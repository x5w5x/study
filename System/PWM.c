#include "stm32f10x.h"

/*

1.RCC开启时钟
2.配置时基单元
3.配置输出比较单元
4.配置GPIO (复用推挽输出)
*/
/**
 * @breif PWM初始化
 * @retval None
 * @attention None
 */
void PWM_Init(void)
{
    //开启GPIOA和TIM2时钟
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //
   //配置GPIOA
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   

   TIM_InternalClockConfig(TIM2); //使用内部时钟
    //配置时基单元
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //时钟分频
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数
   TIM_TimeBaseStructure.TIM_Period=100-1; //计数器周期 ARR
   TIM_TimeBaseStructure.TIM_Prescaler=720-1; //预分频系数 PSC
   TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //重复计数器
   TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure); //初始化定时器2

    //配置输出比较单元
   TIM_OCInitTypeDef TIM_OCInitStructure;//输出比较单元
   TIM_OCStructInit(&TIM_OCInitStructure); //初始化结构体
   TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1; //PWM模式1
   TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High; //输出高极性
   TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable; //输出使能
   TIM_OCInitStructure.TIM_Pulse=50 ; //占空比 CCR
   TIM_OC1Init(TIM2,&TIM_OCInitStructure); //初始化定时器2输出比较单元1

   TIM_Cmd(TIM2,ENABLE); //启动定时器2

//1000HZ占空比50%


}






/**
 * @brief   设置比较值(占空比0-100=0~100%)
 * 
 * @param Compare (0~100)
 */
void PWM_SetCompare1(uint16_t Compare)
{
    TIM_SetCompare1(TIM2,Compare);

}

/**
 * @brief   设置频率
 * 
 * @param Prescaler (720-1:1000HZ)
 */
void PWM_SetPrescaler(uint16_t Prescaler)
{
    TIM_PrescalerConfig(TIM2,Prescaler,TIM_PSCReloadMode_Immediate);
}