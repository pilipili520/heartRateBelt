#include <systick.h>

static int8_t  fac_us = 9;           // 八分频延时微秒的周期
static int16_t fac_ms = 9000;           // 八分频延时毫秒的周期

void delay_us(int32_t nus)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	int32_t temp;
	//nus*fac_us不能超过SysTick->LOAD(24位)-1的值
	SysTick->LOAD = nus*fac_us;    // 设置重载值:n(us)*9需要多少个SysTick时钟周期
	SysTick->VAL = 0x00;                       // 当前值设为0
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ; // 使能嘀嗒定时器
	/*https://blog.csdn.net/csdnyueguoyu/article/details/99682713*/
	do
	{
			temp = SysTick -> CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));    // 使能位countflag位为0或enable位为1则停止循环
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 关闭嘀嗒定时器
	SysTick->VAL = 0X00;                      // 当前值复位为0
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