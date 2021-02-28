#include <USAET.h>

void usart_configer(){
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);//���ڵ�ʱ��ʱ�ӹ�Ӧ�ǵڶ���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//��������Ҫ��ʱ�ӣ�GPIOA��AFIO��USART1
	 GPIO_InitTypeDef GPIO_USART_INIT;
		USART_InitTypeDef USART_INIT;
	NVIC_InitTypeDef NVIC_USART_INIT;
	
	GPIO_USART_INIT.GPIO_Pin = GPIO_Pin_9;
	GPIO_USART_INIT.GPIO_Mode = GPIO_Mode_AF_PP;//�������ͨ�Ļ����ϻ�����ͨ������
	GPIO_USART_INIT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_USART_INIT);
	
	GPIO_USART_INIT.GPIO_Pin = GPIO_Pin_10;
	GPIO_USART_INIT.GPIO_Mode = GPIO_Mode_IN_FLOATING;//����
	GPIO_USART_INIT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_USART_INIT);
	//����Ҫ��С�����һ��
	USART_INIT.USART_BaudRate = 9600;
	USART_INIT.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_INIT.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//������Ҳ�����
	USART_INIT.USART_Parity = USART_Parity_No;//������żУ��λ
	USART_INIT.USART_StopBits = USART_StopBits_1;//ֹͣλ
	USART_INIT.USART_WordLength = USART_WordLength_8b;//����λ�ĳ���
	USART_Init(USART1,&USART_INIT);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_USART_INIT.NVIC_IRQChannel = USART1_IRQn;
	NVIC_USART_INIT.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_USART_INIT.NVIC_IRQChannelSubPriority = 1;
	NVIC_USART_INIT.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_USART_INIT);
	
	
	//��������
	USART_Cmd(USART1,ENABLE);
	//���ڵĳ�ʼ�����
}
//�жϺ����Ƿ���һ�����ж����ȼ�ά���Ķ���

void USART1_sendD(u8 Data){
	USART_SendData(USART1,Data);
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TC));//û�з�����ɾ�һֱ�ȴ�
	USART_ClearFlag(USART1,USART_FLAG_TC);//��ն�Ӧ�ı�־λ
 }
u8 r;
void USART1_IRQHandler(){//������з��͵�ʱ�����

	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET){//���˷��͵�ʱ��������

	r = USART_ReceiveData(USART1);
  
		
	}

	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	USART_ClearITPendingBit(USART1,USART_IT_TXE);//��Ȼû�з��͵������
}