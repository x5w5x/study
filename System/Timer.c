#include"stm32f10x.h"
#include"Timer.h"

/**
 * @breif ��ʱ����ʼ��
 * @param ��
 * @retval ��
 *  1s=72000000/7200=10000
 * period=10000-1
 * prescaler=7200-1
 * 
 * 1ms=72000000/7200/10000
 * period=1000-1
 * prescaler=72-1
 */
//��ʱ1000ms
void Timer_Init(void)
{
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //������ʱ��2ʱ��
   TIM_InternalClockConfig(TIM2); //ʹ���ڲ�ʱ��
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�ӷ�Ƶ
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���
   TIM_TimeBaseStructure.TIM_Period=TIM2_period; //����������
   TIM_TimeBaseStructure.TIM_Prescaler=TIM2_prescaler; //Ԥ��Ƶϵ��
   TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //�ظ�������
   TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure); //��ʼ����ʱ��2



   TIM_ClearFlag(TIM2,TIM_IT_Update); //�����ʱ��2�жϱ�־λ��ֹ��ʼ�������ж�

   TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //ʹ�ܶ�ʱ��2�ж�

   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж����ȼ�����
   NVIC_InitTypeDef NVIC_InitStructure;
   NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //�����ж�ͨ��
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //������ռ���ȼ�
   NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //������Ӧ���ȼ�
   NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //ʹ���ж�ͨ��
   NVIC_Init(&NVIC_InitStructure); //��ʼ���ж�ͨ��

   TIM_Cmd(TIM2,ENABLE); //������ʱ��2
}
/*

*/
/**
 * @breif �ⲿʱ��Դ��ʱ����ʼ��
 * @param ��
 * @retval ��
 *    1s=72000000/7200=10000
 */

void Timer_ETRInit(void){
   

 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //������ʱ��2ʱ��
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //����GPIOAʱ��

 GPIO_InitTypeDef GPIO_InitStructure;
 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//��������
 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 GPIO_Init(GPIOA,&GPIO_InitStructure);

 TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0); //ʹ���ⲿʱ���ڲ�ʱ��



   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�ӷ�Ƶ
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���
   TIM_TimeBaseStructure.TIM_Period=10-1; //����������
   TIM_TimeBaseStructure.TIM_Prescaler=1-1; //Ԥ��Ƶϵ��
   TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //�ظ�������
   TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure); //��ʼ����ʱ��2



   TIM_ClearFlag(TIM2,TIM_IT_Update); 
   TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //ʹ�ܶ�ʱ��2�ж�

   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж����ȼ�����
   NVIC_InitTypeDef NVIC_InitStructure;
   NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //�����ж�ͨ��
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //������ռ���ȼ�
   NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //������Ӧ���ȼ�
   NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //ʹ���ж�ͨ��
   NVIC_Init(&NVIC_InitStructure); //��ʼ���ж�ͨ��

   TIM_Cmd(TIM2,ENABLE); //������ʱ��2





}
// void TIM2_IRQHandler(void)
// {
//    if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //�ж��Ƿ��Ƕ�ʱ��2�ж�
//    {
//     num++;
//       TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //����жϱ�־λ
//       //����ʱ��2�ж�
//    }
// }