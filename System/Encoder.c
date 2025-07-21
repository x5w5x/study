#include"stm32f10x.h"
#include"Delay.h"
int16_t Encoder_Count=0;

// void Encoder_Init(void)
// {
//      //时钟
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //使能GPIOB时钟
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能复用功能时钟
//     //GPIO初始化
//     GPIO_InitTypeDef GPIO_InitStructure;
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOB,&GPIO_InitStructure);

//     //中断初始化
//     GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);//选择外部中断线路
//     GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);//选择外部中断线路
//     //配置EXTI
//    EXTI_InitTypeDef EXTI_InitStructure;
//     EXTI_InitStructure.EXTI_Line = EXTI_Line0|EXTI_Line1;
//     EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//     EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
//     EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//     EXTI_Init(&EXTI_InitStructure);

//     //配置NVIC
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //配置NVIC优先级分组
//     NVIC_InitTypeDef NVIC_InitStructure;
//     NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//选择外部中断线路
//     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级
//     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级
//     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能中断
//     NVIC_Init(&NVIC_InitStructure);

    
//     NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//选择外部中断线路
//     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级
//     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//响应优先级
//     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能中断
//     NVIC_Init(&NVIC_InitStructure);
// }
// int16_t Encoder_Get(void)
// {
   
//     return Encoder_Count;
// }


// void EXTI0_IRQHandler(void)
// {
//     if(EXTI_GetITStatus(EXTI_Line0)==SET){
//         if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0){
//             Encoder_Count--;
//         }
//         EXTI_ClearITPendingBit(EXTI_Line0);
//     }
// }

// void EXTI1_IRQHandler(void)
// {
//     if(EXTI_GetITStatus(EXTI_Line1)==SET){
//         if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0){
//             Encoder_Count++;
//         }
//         EXTI_ClearITPendingBit(EXTI_Line1);
//     }
// }

/*
1.开启时钟
2.配置GPIO(PA6,PA7输入)
3.配置时基单元
4配置捕获/比较寄存器
5.配置编码器接口模式

*/
void Encoder_Init(void)
{
    
   //开启GPIOA和TIM3时钟
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //
   //配置GPIOA
    GPIO_InitTypeDef GPIO_InitStructure;//GPIO初始化结构体
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;//PA6,PA7
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
   

  
    //配置时基单元
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //时钟分频
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数
   TIM_TimeBaseStructure.TIM_Period=65536-1; //计数器周期 ARR
   TIM_TimeBaseStructure.TIM_Prescaler=1-1; //预分频系数 PSC
   TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //重复计数器
   TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); //初始化定时器2
   //配置捕获比较单元
   TIM_ICInitTypeDef TIM_ICInitStructure;
   TIM_ICStructInit(&TIM_ICInitStructure); //初始化捕获比较单元

   TIM_ICInitStructure.TIM_Channel=TIM_Channel_1; //通道1
   TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //上升沿捕获
   TIM_ICInitStructure.TIM_ICFilter=0xF; //滤波器
   TIM_ICInit(TIM3,&TIM_ICInitStructure); //初始化捕获比较单元
   
   TIM_ICInitStructure.TIM_Channel=TIM_Channel_2; //通道2
   TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //上升沿捕获
   TIM_ICInitStructure.TIM_ICFilter=0xF; //滤波器
   TIM_ICInit(TIM3,&TIM_ICInitStructure); //初始化捕获比较单元

   //配置编码器接口模式
   TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising); //编码器接口模式
   TIM_Cmd(TIM3,ENABLE); //使能定时器3
}

// int16_t Encoder_Get(void)
// {
//     return TIM_GetCounter(TIM3);
// }



int16_t Encoder_Get(void)
{
    int16_t Temp;
    Temp=TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3,0);
    return Temp;
    
}