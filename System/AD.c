#include"stm32f10x.h"

/*
1.开启RCC时钟（ADC&GPIO）
2.配置gpio（PA0模拟输入）
3.配置多路开关
4.配置ADC转换器
5.配置ADC中断（看情况）
*/

// void AD_Init(void)
// {
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//开启ADC1时钟
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启GPIOA时钟

//     RCC_ADCCLKConfig(RCC_PCLK2_Div6);//设置ADC时钟为72/6=12MHz

//     //配置GPIOA0为模拟输入
//     GPIO_InitTypeDef GPIO_InitStructure;
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PA0
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
//     GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIOA0
    
//     //配置多路开关
//     ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);//配置ADC1的规则通道，通道0，序列1，采样时间55.5个周期
//     //配置ADC转换器
//     ADC_InitTypeDef ADC_InitStructure;
//     ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
//     ADC_InitStructure.ADC_ScanConvMode = DISABLE;//单通道模式
//     ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//单次转换模式
//     ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//软件触发
//     ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
//     ADC_InitStructure.ADC_NbrOfChannel = 1;//1个通道
//     ADC_Init(ADC1,&ADC_InitStructure);//初始化ADC1

//     //配置ADC中断
//     ADC_Cmd(ADC1,ENABLE);//使能ADC1

//     ADC_ResetCalibration(ADC1);//复位校准
//     while(ADC_GetResetCalibrationStatus(ADC1)==SET);//等待复位校准完成(SET可以省略)

//     ADC_StartCalibration(ADC1);//开始校准
//     while(ADC_GetCalibrationStatus(ADC1)==SET);//等待校准完成(SET可以省略)
    

// }


// uint16_t AD_GetValue(void)
// {
//     ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件启动转换
//     while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);//等待转换完成
//     return ADC_GetConversionValue(ADC1);//返回转换值
// }




void AD_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//开启ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启GPIOA时钟

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//设置ADC时钟为72/6=12MHz

    //配置GPIOA0为模拟输入
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//PA0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
    GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIOA0
    
    //配置多路开关
   
    //配置ADC转换器
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;//单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//单次转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//软件触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;//1个通道
    ADC_Init(ADC1,&ADC_InitStructure);//初始化ADC1

    //配置ADC中断
    ADC_Cmd(ADC1,ENABLE);//使能ADC1

    ADC_ResetCalibration(ADC1);//复位校准
    while(ADC_GetResetCalibrationStatus(ADC1)==SET);//等待复位校准完成(SET可以省略)

    ADC_StartCalibration(ADC1);//开始校准
    while(ADC_GetCalibrationStatus(ADC1)==SET);//等待校准完成(SET可以省略)
    

}


uint16_t AD_GetValue(uint8_t ADC_Channel)
{ ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);//配置ADC1的规则通道，通道0，序列1，采样时间55.5个周期
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件启动转换
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);//等待转换完成
    return ADC_GetConversionValue(ADC1);//返回转换值
}