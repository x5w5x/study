#include"stm32f10x.h"

void Servo_Init(void)
{
    //����GPIOA��TIM2ʱ��
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //
   //����GPIOA
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  

   TIM_InternalClockConfig(TIM2); //ʹ���ڲ�ʱ��
    //����ʱ����Ԫ
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�ӷ�Ƶ
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���
   TIM_TimeBaseStructure.TIM_Period=20000-1; //���������� ARR
   TIM_TimeBaseStructure.TIM_Prescaler=72-1; //Ԥ��Ƶϵ�� PSC
   TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //�ظ�������
   TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure); //��ʼ����ʱ��2

    //��������Ƚϵ�Ԫ
   TIM_OCInitTypeDef TIM_OCInitStructure;//����Ƚϵ�Ԫ
   TIM_OCStructInit(&TIM_OCInitStructure); //��ʼ���ṹ��
   TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1; //PWMģʽ1
   TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High; //����߼���
   TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable; //���ʹ��
   TIM_OCInitStructure.TIM_Pulse=0 ; //ռ�ձ� CCR
   TIM_OC2Init(TIM2,&TIM_OCInitStructure); //��ʼ����ʱ��2����Ƚϵ�Ԫ1

   TIM_Cmd(TIM2,ENABLE); //������ʱ��2




}




void Servo_SetAngle(float angle)
{
    angle=angle/180*2000+500;
    TIM_SetCompare2(TIM2,angle);
}