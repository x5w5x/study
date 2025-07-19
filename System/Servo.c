#include"stm32f10x.h"

void Servo_Init(void)
{
    //开启GPIOA和TIM2时钟
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //
   //配置GPIOA
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  

   TIM_InternalClockConfig(TIM2); //使用内部时钟
    //配置时基单元
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //时钟分频
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数
   TIM_TimeBaseStructure.TIM_Period=20000-1; //计数器周期 ARR
   TIM_TimeBaseStructure.TIM_Prescaler=72-1; //预分频系数 PSC
   TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //重复计数器
   TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure); //初始化定时器2

    //配置输出比较单元
   TIM_OCInitTypeDef TIM_OCInitStructure;//输出比较单元
   TIM_OCStructInit(&TIM_OCInitStructure); //初始化结构体
   TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1; //PWM模式1
   TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High; //输出高极性
   TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable; //输出使能
   TIM_OCInitStructure.TIM_Pulse=0 ; //占空比 CCR
   TIM_OC2Init(TIM2,&TIM_OCInitStructure); //初始化定时器2输出比较单元1

   TIM_Cmd(TIM2,ENABLE); //启动定时器2




}




void Servo_SetAngle(float angle)
{
    angle=angle/180*2000+500;
    TIM_SetCompare2(TIM2,angle);
}