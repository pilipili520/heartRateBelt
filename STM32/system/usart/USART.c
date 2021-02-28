#include <USAET.h>

void usart_configer(){
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);//串口的时钟时钟供应是第二个
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//三个东西要有时钟，GPIOA，AFIO，USART1
	 GPIO_InitTypeDef GPIO_USART_INIT;
		USART_InitTypeDef USART_INIT;
	NVIC_InitTypeDef NVIC_USART_INIT;
	
	GPIO_USART_INIT.GPIO_Pin = GPIO_Pin_9;
	GPIO_USART_INIT.GPIO_Mode = GPIO_Mode_AF_PP;//输出，普通的基础上还是普通的输入
	GPIO_USART_INIT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_USART_INIT);
	
	GPIO_USART_INIT.GPIO_Pin = GPIO_Pin_10;
	GPIO_USART_INIT.GPIO_Mode = GPIO_Mode_IN_FLOATING;//输入
	GPIO_USART_INIT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_USART_INIT);
	//以下要与小软件的一致
	USART_INIT.USART_BaudRate = 9600;
	USART_INIT.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_INIT.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//有输入也有输出
	USART_INIT.USART_Parity = USART_Parity_No;//有无奇偶校验位
	USART_INIT.USART_StopBits = USART_StopBits_1;//停止位
	USART_INIT.USART_WordLength = USART_WordLength_8b;//数据位的长度
	USART_Init(USART1,&USART_INIT);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_USART_INIT.NVIC_IRQChannel = USART1_IRQn;
	NVIC_USART_INIT.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_USART_INIT.NVIC_IRQChannelSubPriority = 1;
	NVIC_USART_INIT.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_USART_INIT);
	
	
	//开启串口
	USART_Cmd(USART1,ENABLE);
	//串口的初始化完成
}
//中断函数是放入一个由中断优先级维护的队列

void USART1_sendD(u8 Data){
	USART_SendData(USART1,Data);
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TC));//没有发送完成就一直等待
	USART_ClearFlag(USART1,USART_FLAG_TC);//清空对应的标志位
 }
u8 r;
void USART1_IRQHandler(){//当外界有发送的时候进入

	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET){//别人发送的时候进入接收

	r = USART_ReceiveData(USART1);
  
		
	}

	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	USART_ClearITPendingBit(USART1,USART_IT_TXE);//虽然没有发送但是情况
}