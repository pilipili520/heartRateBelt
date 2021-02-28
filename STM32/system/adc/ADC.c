#include <ADC.h>

void adc_configer(){
	//ADC的配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_ADC_INIT;
	GPIO_ADC_INIT.GPIO_Pin = GPIO_Pin_5;
	GPIO_ADC_INIT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_ADC_INIT.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_ADC_INIT);
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);//设置ADC分频因子6  72M/6=12,ADC最大时间不能超过14M
	
	ADC_InitTypeDef ADC_init;
	ADC_init.ADC_ContinuousConvMode = DISABLE;
	ADC_init.ADC_Mode = ADC_Mode_Independent;
	ADC_init.ADC_NbrOfChannel = 1;
	ADC_init.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_init.ADC_ScanConvMode = DISABLE;//循环采集，我们只有一个就不开了
	ADC_Init(ADC1,&ADC_init);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5,1,ADC_SampleTime_55Cycles5);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	
	while(ADC_GetCalibrationStatus(ADC1));//检查是ADC1 reset寄存器校准位的最后
	ADC_StartCalibration(ADC1);//开始ADC的校准
	while(ADC_GetCalibrationStatus(ADC1));//校准的最后一位
//	
	
}
u16 Get_ans_ADC(void)
{
 u16 ans;
 ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
 ADC_SoftwareStartConvCmd(ADC1,ENABLE);
 while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
 ans = ADC_GetConversionValue(ADC1);
 return ans;
}