#include"stm32f10x.h"

/*
1.����RCCʱ�ӣ�ADC&GPIO��
2.����gpio��PA0ģ�����룩
3.���ö�·����
4.����ADCת����
5.����ADC�жϣ��������
*/

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




void AD_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//����ADC1ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//����GPIOAʱ��

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//����ADCʱ��Ϊ72/6=12MHz

    //����GPIOA0Ϊģ������
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//PA0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
    GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��GPIOA0
    
    //���ö�·����
   
    //����ADCת����
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//����ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;//1��ͨ��
    ADC_Init(ADC1,&ADC_InitStructure);//��ʼ��ADC1

    //����ADC�ж�
    ADC_Cmd(ADC1,ENABLE);//ʹ��ADC1

    ADC_ResetCalibration(ADC1);//��λУ׼
    while(ADC_GetResetCalibrationStatus(ADC1)==SET);//�ȴ���λУ׼���(SET����ʡ��)

    ADC_StartCalibration(ADC1);//��ʼУ׼
    while(ADC_GetCalibrationStatus(ADC1)==SET);//�ȴ�У׼���(SET����ʡ��)
    

}


uint16_t AD_GetValue(uint8_t ADC_Channel)
{ ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);//����ADC1�Ĺ���ͨ����ͨ��0������1������ʱ��55.5������
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);//�������ת��
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);//�ȴ�ת�����
    return ADC_GetConversionValue(ADC1);//����ת��ֵ
}