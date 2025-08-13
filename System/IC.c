#include"stm32f10x.h"
/*
1.RCC����ʱ��
2.��������GPIO
3.����ʱ����Ԫ
4.���ò���Ƚϵ�Ԫ
5.ѡ���ģʽ����Դ
6.��������

*/
 
// void IC_Init2(void)
// {
//    //����GPIOA��TIM2ʱ��
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //
//    //����GPIOA
//     GPIO_InitTypeDef GPIO_InitStructure;
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOA, &GPIO_InitStructure);
   

//    TIM_InternalClockConfig(TIM3); //ʹ���ڲ�ʱ��
//     //����ʱ����Ԫ
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�ӷ�Ƶ
//    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���
//    TIM_TimeBaseStructure.TIM_Period=65536-1; //���������� ARR
//    TIM_TimeBaseStructure.TIM_Prescaler=72-1; //Ԥ��Ƶϵ�� PSC
//    TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //�ظ�������
//    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); //��ʼ����ʱ��2
//    //���ò���Ƚϵ�Ԫ
//    TIM_ICInitTypeDef TIM_ICInitStructure;
//    TIM_ICInitStructure.TIM_Channel=TIM_Channel_1; //ͨ��1
//    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //�����ز���
//    TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1; //Ԥ��Ƶ
//    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI; //ֱ������
//    TIM_ICInitStructure.TIM_ICFilter=0xF; //�˲���
//    TIM_ICInit(TIM3,&TIM_ICInitStructure); //��ʼ������Ƚϵ�Ԫ
//    //ѡ���ģʽ����Դ
//    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1); //ѡ�����봥��Դ
//    //���ô�ģʽ
//    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset); //ѡ���ģʽ

//    TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��

    
// }


void IC_Init(void)
{
   //����GPIOA��TIM2ʱ��
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //
   //����GPIOA
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   

   TIM_InternalClockConfig(TIM3); //ʹ���ڲ�ʱ��
    //����ʱ����Ԫ
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�ӷ�Ƶ
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���
   TIM_TimeBaseStructure.TIM_Period=65536-1; //���������� ARR
   TIM_TimeBaseStructure.TIM_Prescaler=72-1; //Ԥ��Ƶϵ�� PSC
   TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //�ظ�������
   TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); //��ʼ����ʱ��2
   //���ò���Ƚϵ�Ԫ
   TIM_ICInitTypeDef TIM_ICInitStructure;
   TIM_ICInitStructure.TIM_Channel=TIM_Channel_1; //ͨ��1
   TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //�����ز���
   TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1; //Ԥ��Ƶ
   TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI; //ֱ������
   TIM_ICInitStructure.TIM_ICFilter=0xF; //�˲���
   TIM_PWMIConfig(TIM3,&TIM_ICInitStructure); //��ʼ������Ƚϵ�Ԫ //˫ͨ���Զ�����
   //ѡ���ģʽ����Դ
   TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1); //ѡ�����봥��Դ
   //���ô�ģʽ
   TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset); //ѡ���ģʽ

   TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��

    
}

/**
 * @brief ��ȡƵ��
 * 
 * @return uint32_t 
 */
uint32_t IC_GetFreq(void)
{
    return 1000000/(TIM_GetCapture1(TIM3)+1); //����Ƶ��
}
/**
 * @brief ��ȡռ�ձ�
 * 
 * @return uint32_t 
 */
uint32_t IC_GetDuty(void)
{
    return (TIM_GetCapture2(TIM3)+1)*100/(TIM_GetCapture1(TIM3)+1); //����ռ�ձ�
}