#include <systick.h>

static int8_t  fac_us = 9;           // �˷�Ƶ��ʱ΢�������
static int16_t fac_ms = 9000;           // �˷�Ƶ��ʱ���������

void delay_us(int32_t nus)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	int32_t temp;
	//nus*fac_us���ܳ���SysTick->LOAD(24λ)-1��ֵ
	SysTick->LOAD = nus*fac_us;    // ��������ֵ:n(us)*9��Ҫ���ٸ�SysTickʱ������
	SysTick->VAL = 0x00;                       // ��ǰֵ��Ϊ0
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ; // ʹ����શ�ʱ��
	/*https://blog.csdn.net/csdnyueguoyu/article/details/99682713*/
	do
	{
			temp = SysTick -> CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));    // ʹ��λcountflagλΪ0��enableλΪ1��ֹͣѭ��
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // �ر���શ�ʱ��
	SysTick->VAL = 0X00;                      // ��ǰֵ��λΪ0
}

void delay_ms(int16_t nms)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	int32_t temp;
	SysTick->LOAD = nms*fac_ms;
	SysTick->VAL = 0x00;                       
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ; 
	do
	{
			temp = SysTick -> CTRL;
	}while(!(temp&(1<<16)));    
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; 
	SysTick->VAL = 0X00;
}