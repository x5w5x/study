#include"HCSR04.h"
#include"delay.h"
// uint8_t flag=0;
// uint8_t number=0;
// uint8_t times=0;

// void HCSR04_Init(void)
// {
//     //trig推挽输出 echo浮空输入
//     GPIO_InitTypeDef GPIO_InitStructure;
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOA, &GPIO_InitStructure);

//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOA, &GPIO_InitStructure);

//     // EXTI_InitTypeDef EXTI_InitStructure;
//     // NVIC_InitTypeDef NVIC_InitStructure;
//     // RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//     // GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
//     // EXTI_InitStructure.EXTI_Line = EXTI_Line1;
//     // EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//     // EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//上升沿触发
//     // EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//     // EXTI_Init(&EXTI_InitStructure);

//     // NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
//     // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//     // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//     // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//     // NVIC_Init(&NVIC_InitStructure);
//     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//     TIM_TimeBaseStructure.TIM_Period = 65535;
//     TIM_TimeBaseStructure.TIM_Prescaler = 71;
//     TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//     TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);


// }

// void HCSR04_Start(void)
// {
//     GPIO_SetBits(GPIOA, GPIO_Pin_0);
//     Delay_us(20);
//     GPIO_ResetBits(GPIOA, GPIO_Pin_0);

// }

// float HCSR04_GetDistance(void)
// {
//     while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1));
//     HCSR04_Start();
//     while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1));
//     TIM_SetCounter(TIM2, 0);
//     TIM_Cmd(TIM2, ENABLE);
//     while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1));
//     TIM_Cmd(TIM2, DISABLE);

//     //返回mm
 

//     return (TIM_GetCounter(TIM2))*17;
//     // return (TIM_GetCounter(TIM2))/1000000*340/2 *100;

// }

 
#define HCSR04_TRIG_PORT    GPIOA
#define HCSR04_TRIG_PIN     GPIO_Pin_0
#define HCSR04_ECHO_PORT    GPIOA
#define HCSR04_ECHO_PIN     GPIO_Pin_1

// 初始化函数
void HCSR04_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    

    GPIO_InitStructure.GPIO_Pin = HCSR04_TRIG_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(HCSR04_TRIG_PORT, &GPIO_InitStructure);
    

    GPIO_InitStructure.GPIO_Pin = HCSR04_ECHO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(HCSR04_ECHO_PORT, &GPIO_InitStructure);
    

    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1; // 1MHz计数频率，1us计数一次
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    
    
    GPIO_ResetBits(HCSR04_TRIG_PORT, HCSR04_TRIG_PIN);
}


float HCSR04_GetDistance(void)
{
    uint16_t time = 0;
    float distance = 0;
    
    GPIO_SetBits(HCSR04_TRIG_PORT, HCSR04_TRIG_PIN);
    Delay_us(10); 
    GPIO_ResetBits(HCSR04_TRIG_PORT, HCSR04_TRIG_PIN);
    

    while(GPIO_ReadInputDataBit(HCSR04_ECHO_PORT, HCSR04_ECHO_PIN) == RESET);
    

    TIM_SetCounter(TIM2, 0);
    TIM_Cmd(TIM2, ENABLE);
    
    while(GPIO_ReadInputDataBit(HCSR04_ECHO_PORT, HCSR04_ECHO_PIN) == SET);
    
    // 停止定时器并获取计数值
   TIM_Cmd(TIM2, DISABLE);
    time = TIM_GetCounter(TIM2);
    
    // 计算距离（声速340m/s，距离=时间*340/2 cm）
    distance = time * 0.017*10*1.04;  // time * 340 / 2 / 10000 (us转cm)
    
    return distance;
}