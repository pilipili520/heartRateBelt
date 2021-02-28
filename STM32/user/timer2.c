#include <timer2.h>

void timer2_configer(int psc,int arr){

	TIM_TimeBaseInitTypeDef TIM2_INIT;
	NVIC_InitTypeDef NVIC_INIT;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	{
		TIM2_INIT.TIM_Prescaler = psc;//72分频
		TIM2_INIT.TIM_Period = arr;//重装计算模式放2000
		TIM2_INIT.TIM_CounterMode = TIM_CounterMode_Down;
		TIM2_INIT.TIM_ClockDivision = TIM_CKD_DIV1;
		
		TIM_TimeBaseInit(TIM2, &TIM2_INIT);
			//使能指定的TIM2中断，允许更新中断
		//TIM2_INIT.TIM_RepetitionCounter = 1;
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	}

	{
		
		
		
		NVIC_INIT.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_INIT.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级
		NVIC_INIT.NVIC_IRQChannelSubPriority = 1;//响应优先级
		NVIC_INIT.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_INIT);
	}

		TIM_Cmd(TIM2, ENABLE);//忘了给时钟使能了
}

//中断是指的是中断函数对应的事件的优先级吗
void TIM2_IRQHandler(void)//startup_stm32f10x_md.s中定义好的
{
	int cnt = 0;
	//if(cnt >3)GPIO_SetBits(GPIOA, GPIO_Pin_3);
	if(TIM_GetITStatus(TIM2 , TIM_IT_Update) == SET ){//先看是不是设置的中断，防止受到干扰，是一个安全机制
		if(cnt < 1000){
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
			//cnt = ~cnt;
		cnt++;
		}
		else if(cnt >= 1000 && cnt <2000){
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			cnt++;
		}
		else if(cnt >= 2000){
			cnt = 0;
		}
			
	//	return;
	}
	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//计数器到零，清除对应的标志位
}
	