#include <ADC.h>

void adc_configer(){
	//ADC������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_ADC_INIT;
	GPIO_ADC_INIT.GPIO_Pin = GPIO_Pin_5;
	GPIO_ADC_INIT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_ADC_INIT.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_ADC_INIT);
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);//����ADC��Ƶ����6  72M/6=12,ADC���ʱ�䲻�ܳ���14M
	
	ADC_InitTypeDef ADC_init;
	ADC_init.ADC_ContinuousConvMode = DISABLE;
	ADC_init.ADC_Mode = ADC_Mode_Independent;
	ADC_init.ADC_NbrOfChannel = 1;
	ADC_init.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_init.ADC_ScanConvMode = DISABLE;//ѭ���ɼ�������ֻ��һ���Ͳ�����
	ADC_Init(ADC1,&ADC_init);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5,1,ADC_SampleTime_55Cycles5);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	
	while(ADC_GetCalibrationStatus(ADC1));//�����ADC1 reset�Ĵ���У׼λ�����
	ADC_StartCalibration(ADC1);//��ʼADC��У׼
	while(ADC_GetCalibrationStatus(ADC1));//У׼�����һλ
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