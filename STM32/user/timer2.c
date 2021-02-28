#include <timer2.h>

void timer2_configer(int psc,int arr){

	TIM_TimeBaseInitTypeDef TIM2_INIT;
	NVIC_InitTypeDef NVIC_INIT;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	{
		TIM2_INIT.TIM_Prescaler = psc;//72��Ƶ
		TIM2_INIT.TIM_Period = arr;//��װ����ģʽ��2000
		TIM2_INIT.TIM_CounterMode = TIM_CounterMode_Down;
		TIM2_INIT.TIM_ClockDivision = TIM_CKD_DIV1;
		
		TIM_TimeBaseInit(TIM2, &TIM2_INIT);
			//ʹ��ָ����TIM2�жϣ���������ж�
		//TIM2_INIT.TIM_RepetitionCounter = 1;
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	}

	{
		
		
		
		NVIC_INIT.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_INIT.NVIC_IRQChannelPreemptionPriority = 2;//��ռ���ȼ�
		NVIC_INIT.NVIC_IRQChannelSubPriority = 1;//��Ӧ���ȼ�
		NVIC_INIT.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_INIT);
	}

		TIM_Cmd(TIM2, ENABLE);//���˸�ʱ��ʹ����
}

//�ж���ָ�����жϺ�����Ӧ���¼������ȼ���
void TIM2_IRQHandler(void)//startup_stm32f10x_md.s�ж���õ�
{
	int cnt = 0;
	//if(cnt >3)GPIO_SetBits(GPIOA, GPIO_Pin_3);
	if(TIM_GetITStatus(TIM2 , TIM_IT_Update) == SET ){//�ȿ��ǲ������õ��жϣ���ֹ�ܵ����ţ���һ����ȫ����
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
	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//���������㣬�����Ӧ�ı�־λ
}
	