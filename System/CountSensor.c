#include"stm32f10x.h"
#include "Delay.h"
uint16_t count=0;
void CountSensor_Init(void)
{
    //时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //使能GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能复用功能时钟
    //GPIO初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    //中断初始化
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);//选择外部中断线路
    //配置EXTI
   EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//上升沿下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    //配置NVIC
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //配置NVIC优先级分组
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//选择外部中断线路
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能中断
    NVIC_Init(&NVIC_InitStructure);

}
uint16_t GetCount(void)
{
    return count;
}
void EXTI15_10_IRQHandler(void)
{
    Delay_ms(100);//消抖
    if(EXTI_GetITStatus(EXTI_Line14)==SET)//判断是否是EXTI_Line14触发的中断
    {
        count++;
        EXTI_ClearITPendingBit(EXTI_Line14);//清除中断标志位
    }
}