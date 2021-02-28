#include <key.h>
#include <led.h>
#include <systick.h>

void key_configer(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_KEY_INIT;
	GPIO_KEY_INIT.GPIO_Pin = GPIO_Pin_0;
	GPIO_KEY_INIT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_KEY_INIT.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_KEY_INIT);
}

int key_scan(void)
{
	while(1){
		key_configer();
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
			return 0;
		else return 1;
	}
}

void light_control(void)
{
	while(1)
	{
		if(key_scan() == 1)
		{
			while(key_scan() == 1)
				waterfall_light();
				one_light_off();
		}
		else one_light_off();
	}
}

void light_change(void)
{
	int count=0;
	while(1)
	{
		if(key_scan() == 1)
		{
			delay_ms(50);
			if(key_scan() == 0)
			{
				count++;
				count = count%2;
			}
			else continue;
			if(count%2 == 0)
				one_light_on();
			else
				one_light_off();
		}
		else continue;
	}
}