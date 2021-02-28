#include <timer.h>
#include <systick.h>


//T=((psc+1)/Sys_clk)*(arr+1)

//ͨ�ö�ʱ��3�жϳ�ʼ��
void TIM2_Configer(int16_t arr, int16_t psc) //arr�Զ���װ��ֵ��psc��Ƶֵ
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//GPIO_SetBits(GPIOA, GPIO_Pin_1);

	//ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//		GPIO_SetBits(GPIOA, GPIO_Pin_1);

	//	//�ж����ȼ�����
	{
		//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	}
	delay_ms(1500);
	//��ʱ��TIM2��������
	{
		TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ��ֵ
		TIM_TimeBaseStructure.TIM_Prescaler = psc; //��Ƶֵ
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
		//ʹ��ָ����TIM2�жϣ���������ж�
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	}
//		GPIO_SetBits(GPIOA, GPIO_Pin_1);

	

//	//�ж����ȼ�����
//	{
//		//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	}
			
			//GPIO_SetBits(GPIOA, GPIO_Pin_1);
	
	NVIC_Init(&NVIC_InitStructure);//TODO BUG
	

	//ʹ��TIM2
	TIM_Cmd(TIM2, ENABLE);
	//TIM_IRQHandler();
}

//TIM2�жϷ������
void TIM2_IRQHandler(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���TIM2�����жϷ������
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //���TIM2�����жϱ�־
		timer_state = 1;
	}
}
	
	
	