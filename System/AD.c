#include"stm32f10x.h"

/*
1.����RCCʱ�ӣ�ADC&GPIO��
2.����gpio��PA0ģ�����룩
3.���ö�·����
4.����ADCת����
5.����ADC�жϣ��������
*/
//����
// void AD_Init(void)
// {
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//����ADC1ʱ��
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//����GPIOAʱ��

//     RCC_ADCCLKConfig(RCC_PCLK2_Div6);//����ADCʱ��Ϊ72/6=12MHz

//     //����GPIOA0Ϊģ������
//     GPIO_InitTypeDef GPIO_InitStructure;
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PA0
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ������
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
//     GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��GPIOA0
    
//     //���ö�·����
//     ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);//����ADC1�Ĺ���ͨ����ͨ��0������1������ʱ��55.5������
//     //����ADCת����
//     ADC_InitTypeDef ADC_InitStructure;
//     ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
//     ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ͨ��ģʽ
//     ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//����ת��ģʽ
//     ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������
//     ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
//     ADC_InitStructure.ADC_NbrOfChannel = 1;//1��ͨ��
//     ADC_Init(ADC1,&ADC_InitStructure);//��ʼ��ADC1

//     //����ADC�ж�
//     ADC_Cmd(ADC1,ENABLE);//ʹ��ADC1

//     ADC_ResetCalibration(ADC1);//��λУ׼
//     while(ADC_GetResetCalibrationStatus(ADC1)==SET);//�ȴ���λУ׼���(SET����ʡ��)

//     ADC_StartCalibration(ADC1);//��ʼУ׼
//     while(ADC_GetCalibrationStatus(ADC1)==SET);//�ȴ�У׼���(SET����ʡ��)
    

// }


// uint16_t AD_GetValue(void)
// {
//     ADC_SoftwareStartConvCmd(ADC1,ENABLE);//�������ת��
//     while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);//�ȴ�ת�����
//     return ADC_GetConversionValue(ADC1);//����ת��ֵ
// }


//���

// void AD_Init(void)
// {
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//����ADC1ʱ��
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//����GPIOAʱ��

//     RCC_ADCCLKConfig(RCC_PCLK2_Div6);//����ADCʱ��Ϊ72/6=12MHz

//     //����GPIOA0Ϊģ������
//     GPIO_InitTypeDef GPIO_InitStructure;
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//PA0
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ������
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
//     GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��GPIOA0
    
//     //���ö�·����
   
//     //����ADCת����
//     ADC_InitTypeDef ADC_InitStructure;
//     ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
//     ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ͨ��ģʽ
//     ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//����ת��ģʽ
//     ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������
//     ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
//     ADC_InitStructure.ADC_NbrOfChannel = 1;//1��ͨ��
//     ADC_Init(ADC1,&ADC_InitStructure);//��ʼ��ADC1

//     //����ADC�ж�
//     ADC_Cmd(ADC1,ENABLE);//ʹ��ADC1

//     ADC_ResetCalibration(ADC1);//��λУ׼
//     while(ADC_GetResetCalibrationStatus(ADC1)==SET);//�ȴ���λУ׼���(SET����ʡ��)

//     ADC_StartCalibration(ADC1);//��ʼУ׼
//     while(ADC_GetCalibrationStatus(ADC1)==SET);//�ȴ�У׼���(SET����ʡ��)
    

// }


// uint16_t AD_GetValue(uint8_t ADC_Channel)
// { ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);//����ADC1�Ĺ���ͨ����ͨ��0������1������ʱ��55.5������
//     ADC_SoftwareStartConvCmd(ADC1,ENABLE);//�������ת��
//     while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);//�ȴ�ת�����
//     return ADC_GetConversionValue(ADC1);//����ת��ֵ
// }

//DMA
uint16_t AD_Value[4];

void AD_Init(void)
{

/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	//����ADC1��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//����GPIOA��ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		//����DMA1��ʱ��
	
	/*����ADCʱ��*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);						//ѡ��ʱ��6��Ƶ��ADCCLK = 72MHz / 6 = 12MHz(ADCʱ�����Ϊ14MHz)
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//��PA0��PA1��PA2��PA3���ų�ʼ��Ϊģ������
	
	/*������ͨ������*/
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);	//����������1��λ�ã�����Ϊͨ��0
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);	//����������2��λ�ã�����Ϊͨ��1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);	//����������3��λ�ã�����Ϊͨ��2
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);	//����������4��λ�ã�����Ϊͨ��3
	
	/*ADC��ʼ��*/
	ADC_InitTypeDef ADC_InitStructure;											//����ṹ�����
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;							//ģʽ��ѡ�����ģʽ��������ʹ��ADC1
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						//���ݶ��룬ѡ���Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;			//�ⲿ������ʹ���������������Ҫ�ⲿ����
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;							//����ת����ʹ�ܣ�ÿת��һ�ι��������к����̿�ʼ��һ��ת��
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;								//ɨ��ģʽ��ʹ�ܣ�ɨ�����������У�ɨ��������ADC_NbrOfChannelȷ��
	ADC_InitStructure.ADC_NbrOfChannel = 4;										//ͨ������Ϊ4��ɨ��������ǰ4��ͨ��
	ADC_Init(ADC1, &ADC_InitStructure);											//���ṹ���������ADC_Init������ADC1
	
	/*DMA��ʼ��*/
	DMA_InitTypeDef DMA_InitStructure;											//����ṹ�����
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;				//�������ַ�������β�AddrA
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//�������ݿ�ȣ�ѡ����֣���Ӧ16Ϊ��ADC���ݼĴ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			//�����ַ������ѡ��ʧ�ܣ�ʼ����ADC���ݼĴ���ΪԴ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;					//�洢������ַ���������ADת�������ȫ������AD_Value
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			//�洢�����ݿ�ȣ�ѡ����֣���Դ���ݿ�ȶ�Ӧ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						//�洢����ַ������ѡ��ʹ�ܣ�ÿ��ת�˺������Ƶ���һ��λ��
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;							//���ݴ��䷽��ѡ�������赽�洢����ADC���ݼĴ���ת������
	DMA_InitStructure.DMA_BufferSize = 4;										//ת�˵����ݴ�С��ת�˴���������ADCͨ����һ��
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;								//ģʽ��ѡ��ѭ��ģʽ����ADC������ת��һ��
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;								//�洢�����洢����ѡ��ʧ�ܣ�������ADC���败��ת�˵��洢��
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;						//���ȼ���ѡ���е�
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);								//���ṹ���������DMA_Init������DMA1��ͨ��1
	
	/*DMA��ADCʹ��*/
	DMA_Cmd(DMA1_Channel1, ENABLE);							//DMA1��ͨ��1ʹ��
	ADC_DMACmd(ADC1, ENABLE);								//ADC1����DMA1���ź�ʹ��
	ADC_Cmd(ADC1, ENABLE);									//ADC1ʹ��
	
	/*ADCУ׼*/
	ADC_ResetCalibration(ADC1);								//�̶����̣��ڲ��е�·���Զ�ִ��У׼
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
	
	/*ADC����*/
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	//�������ADC��ʼ����������ADC��������ת��ģʽ���ʴ���һ�κ�ADC�Ϳ���һֱ�������ϵع���

}


