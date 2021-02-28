#include <timer.h>
#include <systick.h>


//T=((psc+1)/Sys_clk)*(arr+1)

//通用定时器3中断初始化
void TIM2_Configer(int16_t arr, int16_t psc) //arr自动重装载值，psc分频值
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//GPIO_SetBits(GPIOA, GPIO_Pin_1);

	//时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//		GPIO_SetBits(GPIOA, GPIO_Pin_1);

	//	//中断优先级设置
	{
		//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	}
	delay_ms(1500);
	//定时器TIM2参数配置
	{
		TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载值
		TIM_TimeBaseStructure.TIM_Prescaler = psc; //分频值
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
		//使能指定的TIM2中断，允许更新中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	}
//		GPIO_SetBits(GPIOA, GPIO_Pin_1);

	

//	//中断优先级设置
//	{
//		//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	}
			
			//GPIO_SetBits(GPIOA, GPIO_Pin_1);
	
	NVIC_Init(&NVIC_InitStructure);//TODO BUG
	

	//使能TIM2
	TIM_Cmd(TIM2, ENABLE);
	//TIM_IRQHandler();
}

//TIM2中断服务程序
void TIM2_IRQHandler(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查TIM2更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //清楚TIM2更新中断标志
		timer_state = 1;
	}
}
	
	
	