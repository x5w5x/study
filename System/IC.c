#include"stm32f10x.h"
/*
1.RCC开启时钟
2.配置引脚GPIO
3.配置时基单元
4.配置捕获比较单元
5.选择从模式触发源
6.后续配置

*/
 
// void IC_Init2(void)
// {
//    //开启GPIOA和TIM2时钟
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //
//    //配置GPIOA
//     GPIO_InitTypeDef GPIO_InitStructure;
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOA, &GPIO_InitStructure);
   

//    TIM_InternalClockConfig(TIM3); //使用内部时钟
//     //配置时基单元
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //时钟分频
//    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数
//    TIM_TimeBaseStructure.TIM_Period=65536-1; //计数器周期 ARR
//    TIM_TimeBaseStructure.TIM_Prescaler=72-1; //预分频系数 PSC
//    TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //重复计数器
//    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); //初始化定时器2
//    //配置捕获比较单元
//    TIM_ICInitTypeDef TIM_ICInitStructure;
//    TIM_ICInitStructure.TIM_Channel=TIM_Channel_1; //通道1
//    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //上升沿捕获
//    TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1; //预分频
//    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI; //直接输入
//    TIM_ICInitStructure.TIM_ICFilter=0xF; //滤波器
//    TIM_ICInit(TIM3,&TIM_ICInitStructure); //初始化捕获比较单元
//    //选择从模式触发源
//    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1); //选择输入触发源
//    //配置从模式
//    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset); //选择从模式

//    TIM_Cmd(TIM3,ENABLE); //使能定时器

    
// }


void IC_Init(void)
{
   //开启GPIOA和TIM2时钟
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //
   //配置GPIOA
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   

   TIM_InternalClockConfig(TIM3); //使用内部时钟
    //配置时基单元
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //时钟分频
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数
   TIM_TimeBaseStructure.TIM_Period=65536-1; //计数器周期 ARR
   TIM_TimeBaseStructure.TIM_Prescaler=72-1; //预分频系数 PSC
   TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //重复计数器
   TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); //初始化定时器2
   //配置捕获比较单元
   TIM_ICInitTypeDef TIM_ICInitStructure;
   TIM_ICInitStructure.TIM_Channel=TIM_Channel_1; //通道1
   TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //上升沿捕获
   TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1; //预分频
   TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI; //直接输入
   TIM_ICInitStructure.TIM_ICFilter=0xF; //滤波器
   TIM_PWMIConfig(TIM3,&TIM_ICInitStructure); //初始化捕获比较单元 //双通道自动配置
   //选择从模式触发源
   TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1); //选择输入触发源
   //配置从模式
   TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset); //选择从模式

   TIM_Cmd(TIM3,ENABLE); //使能定时器

    
}

/**
 * @brief 获取频率
 * 
 * @return uint32_t 
 */
uint32_t IC_GetFreq(void)
{
    return 1000000/(TIM_GetCapture1(TIM3)+1); //返回频率
}
/**
 * @brief 获取占空比
 * 
 * @return uint32_t 
 */
uint32_t IC_GetDuty(void)
{
    return (TIM_GetCapture2(TIM3)+1)*100/(TIM_GetCapture1(TIM3)+1); //返回占空比
}