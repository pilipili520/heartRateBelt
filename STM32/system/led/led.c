#include <led.h>
#include <key.h>
#include <systick.h>

void led_configer(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_LED_INIT;
	GPIO_LED_INIT.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_LED_INIT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_LED_INIT.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_LED_INIT);
}

void waterfall_light(void){
	led_configer();
	while(1)
	{
		if(key_scan() == 0)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_4);
			continue;
		}
		else 
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_4);
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
			delay_ms(1000);
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
			delay_ms(1000);
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
			GPIO_SetBits(GPIOA, GPIO_Pin_3);
			delay_ms(1000);
			GPIO_ResetBits(GPIOA, GPIO_Pin_3);
			GPIO_SetBits(GPIOA, GPIO_Pin_4);
			delay_ms(1000);
		}
	}
}

void flash_light(void){
	int t = 1000000;
	led_configer();
	while(1)
	{
		if(key_scan() == 0)
			continue;
		else 
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
			delay_ms(1000);
			GPIO_ResetBits(GPIOA, GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
			delay_ms(1000);
		}
	}
}

void one_light_on(void){
	led_configer();
	GPIO_SetBits(GPIOA, GPIO_Pin_1);	
}

void one_light_off(void){
	led_configer();
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);	
}

void all_lights_on(void){
	led_configer();
	GPIO_SetBits(GPIOA, GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);	
}
