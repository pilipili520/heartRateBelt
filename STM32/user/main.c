#include <stdio.h>
#include <stm32f10x.h>
#include <led.h>
#include <key.h>
#include <systick.h>
#include <timer2.h>
#include <USAET.h>
#include <math.h>
#include <ADC.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b)) 
#define min(a, b) ((a) < (b) ? (a) : (b))
#define buff_size		50	
#define SAMPLE_PERIOD	20	

uint16_t Get_Array_Max(uint16_t * array, uint32_t size);
uint16_t Get_Array_Min(uint16_t * array, uint32_t size);

typedef enum {FALSE, TRUE} BOOL;

uint16_t readData, lastReadData;		   		
uint16_t Time_Count = 0;         
uint16_t firstTimeCount = 0;    
uint16_t secondTimeCount = 0;


uint16_t IBI, BPM, SIG; 
uint16_t data[buff_size] = {0}; 
uint16_t tdata[buff_size] = {0};
int ttcnt = -1;

uint8_t cnt = 0; 			
uint16_t max, min, mid;			
uint16_t filter;	

BOOL PULSE = FALSE;			
BOOL PRE_PULSE = FALSE;         

uint8_t pulseCount = 0;
uint32_t i;

char Reversal = 0;

 // u16 new_data[1050] = {0};
void send_data(int flag)
{
	int number[3];
	for(int i=2;i>=0;i--)
	{
		number[i] = flag % 10;
		flag = flag / 10;
	}
	for(int i=0;i<=2;i++)
	{
		USART_SendData(USART1, number[i]+'0');
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}
	}
	USART_SendData(USART1, 0x0D);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}
	USART_SendData(USART1, 0x0A);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}
		
}
int main () 
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级分组，分一次
	// 先占式优先级就是所谓的抢占式优先级，比如一个设置为0，一个设置为2，则在2执行中断时，
	// 如果0来了，暂停2的，马上执行0的。从优先级就是设定一个中断执行的顺序，当两个中断来时，
	// 哪个优先级高执行哪个，但同一个强占优先级不同的从优先级，不能抢占那个从优先级低的
	led_configer();
//	timer2_configer(71,1999);//分频，周期

	usart_configer();
	adc_configer();
	u16 DataValue; 
	while(1){
		lastReadData = readData;	       
		    readData = Get_ans_ADC();
	if ((readData - lastReadData) < filter)    //加了一个过滤
			     data[cnt ++] = readData;	
	if (cnt >= buff_size ){	//大于50，就找一个最大最小值，所以开始的那些都是错的，就是cnt < buff_size的都是错的，要等一会
			cnt = 0;	
		  max = Get_Array_Max(data, buff_size );//找到数组最大
			min = Get_Array_Min(data, buff_size );//找到数组最小
		  mid = (max + min)/2;//找到中间的数
			filter = (max - min) / 2;//找到过滤的，那些特别大的就是噪声，这个是学的网上的大佬的
	}
	PRE_PULSE = PULSE;//这两个的初始化都是False,如果前一个不大于mid，当前的那个大于
	PULSE = (readData > mid) ? TRUE : FALSE;//如果这个数大于中间值就算是TRUE
	if (PRE_PULSE == FALSE && PULSE == TRUE) {//如果前一个不大于中间，后一个大于中间就算一次
		pulseCount++;//第一次的增加1
		pulseCount %= 2;
		if(pulseCount == 1) { //如果这个是第一次数就是Time_Count                        	
				firstTimeCount = Time_Count;  //开始计时
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		}
		if(pulseCount == 0)  {  //如果是第二次      停止计时                     			
				secondTimeCount = Time_Count;  //Time_Count 计算的是两次的之间的采样次数
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
				Time_Count = 0;//归零
				if ( (secondTimeCount > firstTimeCount)){//如果第二次的大于第一次的
					IBI = (secondTimeCount - firstTimeCount) * SAMPLE_PERIOD;	// IBI，两次间隔
					BPM = 60000 / IBI;  // IBI -> BPM
					
					if (BPM > 200)   
						BPM = 200;	 				
					if (BPM < 30) 
						BPM=30;
				}
			
			}
		if(BPM >= 60 && BPM <= 100){
			USART_SendData(USART1, ' ');
			USART_SendData(USART1, 'B');
			while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}		
			send_data(BPM);
		}
				
//		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}		
			u16 res = 0;
//			if(BPM < 130){
//				tdata[++ttcnt] = BPM;
//				if(ttcnt == 10){
//					ttcnt = 0;
//					u16 m = rever(tdata);
//					if(m >= 60 && m <= 120){
//						res = m;
//					}
//						
//				}
//			}
			
		}
	
			SIG = readData/5;
			Time_Count++;  // 
			delay_ms(SAMPLE_PERIOD);
	}
	
	return 0;
}
uint16_t Get_Array_Max(uint16_t * array, uint32_t size)
{
	uint16_t max = array[0];
	uint32_t i;
	
	for (i = 1; i < size; i++)
	{
		if (array[i] > max)
			max = data[i];
	}
	
	return max;
}


uint16_t Get_Array_Min(uint16_t * array, uint32_t size)
{
	uint16_t min = array[0];
	uint32_t i;
	
	for (i = 1; i < size; i++)
	{
		if (array[i] < min)
			min = data[i];
	}
	
	return min;
}
//int main()
//	{
//	light_change();
//	return 0;
//}