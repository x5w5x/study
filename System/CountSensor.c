#include"stm32f10x.h"
#include "Delay.h"
uint16_t count=0;
void CountSensor_Init(void)
{
    //ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ�ܸ��ù���ʱ��
    //GPIO��ʼ��
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    //�жϳ�ʼ��
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);//ѡ���ⲿ�ж���·
    //����EXTI
   EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�������½��ش���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    //����NVIC
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC���ȼ�����
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//ѡ���ⲿ�ж���·
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//��Ӧ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж�
    NVIC_Init(&NVIC_InitStructure);

}
uint16_t GetCount(void)
{
    return count;
}
void EXTI15_10_IRQHandler(void)
{
    Delay_ms(100);//����
    if(EXTI_GetITStatus(EXTI_Line14)==SET)//�ж��Ƿ���EXTI_Line14�������ж�
    {
        count++;
        EXTI_ClearITPendingBit(EXTI_Line14);//����жϱ�־λ
    }
}