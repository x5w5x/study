#include"stm32f10x.h"
/**
 * @brief    ��ʼ�����
 *  @note ���� PA0(PA15) PA1(PB3) PA2(PB10) PA3(PB11) 
 * @note ��ע:  TIM2��ͨ��1��ӦPA0,ͨ��2��ӦPA1,ͨ��3��ӦPA2,ͨ��4��ӦPA3
 */
void Servo_Init(void)
{
    //����GPIOA��TIM2ʱ��
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //
   //����GPIOA
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//���ö������һ���޸�ע���޸�TIM_OC(X)Init����
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
   //ע��:  TIM2��ͨ��1��ӦPA0,ͨ��2��ӦPA1,ͨ��3��ӦPA2,ͨ��4��ӦPA3
   TIM_OC1Init(TIM2,&TIM_OCInitStructure); //��ʼ����ʱ��2����Ƚϵ�Ԫ0
   TIM_OC2Init(TIM2,&TIM_OCInitStructure); //��ʼ����ʱ��2����Ƚϵ�Ԫ1
   TIM_OC3Init(TIM2,&TIM_OCInitStructure); //��ʼ����ʱ��2����Ƚϵ�Ԫ2
   TIM_OC4Init(TIM2,&TIM_OCInitStructure); //��ʼ����ʱ��2����Ƚϵ�Ԫ3

   TIM_Cmd(TIM2,ENABLE); //������ʱ��2
}



/**
 * @brief    ���ö���Ƕ�
 *  @param servo ������ PA0
 * @param angle �Ƕ�
 */
void Servo1_SetAngle(float angle)
{
    angle=angle/180*2000+500;
    TIM_SetCompare1(TIM2,angle); //��ӦPA1
}

/**
 * @brief    ���ö���Ƕ�
 * @param servo ������ PA2
 * @param angle    �Ƕ�
 */
void Servo2_SetAngle(float angle)
{
    angle=angle/180*2000+500;
    TIM_SetCompare2(TIM2,angle);//��ӦPA2
}

/**
 * @brief    ���ö���Ƕ�
 * @param servo ������ PA3
 * @param angle  �Ƕ�
 */
void Servo3_SetAngle(float angle)
{
    angle=angle/180*2000+500;
    TIM_SetCompare3(TIM2,angle);//��ӦPA3
}
/**
 * @brief    ���ö���Ƕ�
 * @param servo ������ PA4
 *  @param angle �Ƕ�
 */
void Servo4_SetAngle(float angle)
{
    angle=angle/180*2000+500;
    TIM_SetCompare2(TIM2,angle);//��ӦPA0
}
/**
 * @brief   ���ö���Ƕ�
 * @param servo ������
 * @param angle  �Ƕ�
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