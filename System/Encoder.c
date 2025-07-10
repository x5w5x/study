#include"stm32f10x.h"
#include"Delay.h"
int16_t Encoder_Count=0;

void Encoder_Init(void)
{
     //时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //使能GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能复用功能时钟
    //GPIO初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    //中断初始化
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);//选择外部中断线路
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);//选择外部中断线路
    //配置EXTI
   EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line0|EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    //配置NVIC
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //配置NVIC优先级分组
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//选择外部中断线路
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能中断
    NVIC_Init(&NVIC_InitStructure);

    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//选择外部中断线路
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能中断
    NVIC_Init(&NVIC_InitStructure);
}
int16_t Encoder_Get(void)
{
   
    return Encoder_Count;
}


void EXTI0_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0)==SET){
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0){
            Encoder_Count--;
        }
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

void EXTI1_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line1)==SET){
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0){
            Encoder_Count++;
        }
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}