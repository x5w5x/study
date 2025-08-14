#include"stm32f10x.h"
/**
 * @brief    初始化舵机
 *  @note 引脚 PA0(PA15) PA1(PB3) PA2(PB10) PA3(PB11) 
 * @note 备注:  TIM2的通道1对应PA0,通道2对应PA1,通道3对应PA2,通道4对应PA3
 */
void Servo_Init(void)
{
    //开启GPIOA和TIM2时钟
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //
   //配置GPIOA
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//设置舵机引脚一旦修改注意修改TIM_OC(X)Init函数
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
   //注意:  TIM2的通道1对应PA0,通道2对应PA1,通道3对应PA2,通道4对应PA3
   TIM_OC1Init(TIM2,&TIM_OCInitStructure); //初始化定时器2输出比较单元0
   TIM_OC2Init(TIM2,&TIM_OCInitStructure); //初始化定时器2输出比较单元1
   TIM_OC3Init(TIM2,&TIM_OCInitStructure); //初始化定时器2输出比较单元2
   TIM_OC4Init(TIM2,&TIM_OCInitStructure); //初始化定时器2输出比较单元3

   TIM_Cmd(TIM2,ENABLE); //启动定时器2
}



/**
 * @brief    设置舵机角度
 *  @param servo 舵机编号 PA0
 * @param angle 角度
 */
void Servo1_SetAngle(float angle)
{
    angle=angle/180*2000+500;
    TIM_SetCompare1(TIM2,angle); //对应PA1
}

/**
 * @brief    设置舵机角度
 * @param servo 舵机编号 PA2
 * @param angle    角度
 */
void Servo2_SetAngle(float angle)
{
    angle=angle/180*2000+500;
    TIM_SetCompare2(TIM2,angle);//对应PA2
}

/**
 * @brief    设置舵机角度
 * @param servo 舵机编号 PA3
 * @param angle  角度
 */
void Servo3_SetAngle(float angle)
{
    angle=angle/180*2000+500;
    TIM_SetCompare3(TIM2,angle);//对应PA3
}
/**
 * @brief    设置舵机角度
 * @param servo 舵机编号 PA4
 *  @param angle 角度
 */
void Servo4_SetAngle(float angle)
{
    angle=angle/180*2000+500;
    TIM_SetCompare2(TIM2,angle);//对应PA0
}
/**
 * @brief   设置舵机角度
 * @param servo 舵机编号
 * @param angle  角度
 */
void Servo_SetAngle(uint8_t servo,float angle)
{
    angle=angle/180*2000+500;
    switch(servo)
    {
        case 1:TIM_SetCompare1(TIM2,angle);break;
        case 2:TIM_SetCompare2(TIM2,angle);break;
        case 3:TIM_SetCompare3(TIM2,angle);break;
        case 4:TIM_SetCompare4(TIM2,angle);break;
    }
}