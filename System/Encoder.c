#include"stm32f10x.h"
#include"Delay.h"
int16_t Encoder_Count=0;

// void Encoder_Init(void)
// {
//      //ʱ��
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ�ܸ��ù���ʱ��
//     //GPIO��ʼ��
//     GPIO_InitTypeDef GPIO_InitStructure;
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOB,&GPIO_InitStructure);

//     //�жϳ�ʼ��
//     GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);//ѡ���ⲿ�ж���·
//     GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);//ѡ���ⲿ�ж���·
//     //����EXTI
//    EXTI_InitTypeDef EXTI_InitStructure;
//     EXTI_InitStructure.EXTI_Line = EXTI_Line0|EXTI_Line1;
//     EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//     EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
//     EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//     EXTI_Init(&EXTI_InitStructure);

//     //����NVIC
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC���ȼ�����
//     NVIC_InitTypeDef NVIC_InitStructure;
//     NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//ѡ���ⲿ�ж���·
//     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�
//     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//��Ӧ���ȼ�
//     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж�
//     NVIC_Init(&NVIC_InitStructure);

    
//     NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//ѡ���ⲿ�ж���·
//     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�
//     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//��Ӧ���ȼ�
//     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж�
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
1.����ʱ��
2.����GPIO(PA6,PA7����)
3.����ʱ����Ԫ
4���ò���/�ȽϼĴ���
5.���ñ������ӿ�ģʽ

*/
void Encoder_Init(void)
{
    
   //����GPIOA��TIM3ʱ��
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //
   //����GPIOA
    GPIO_InitTypeDef GPIO_InitStructure;//GPIO��ʼ���ṹ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;//PA6,PA7
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA
   

  
    //����ʱ����Ԫ
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�ӷ�Ƶ
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���
   TIM_TimeBaseStructure.TIM_Period=65536-1; //���������� ARR
   TIM_TimeBaseStructure.TIM_Prescaler=1-1; //Ԥ��Ƶϵ�� PSC
   TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //�ظ�������
   TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); //��ʼ����ʱ��2
   //���ò���Ƚϵ�Ԫ
   TIM_ICInitTypeDef TIM_ICInitStructure;
   TIM_ICStructInit(&TIM_ICInitStructure); //��ʼ������Ƚϵ�Ԫ

   TIM_ICInitStructure.TIM_Channel=TIM_Channel_1; //ͨ��1
   TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //�����ز���
   TIM_ICInitStructure.TIM_ICFilter=0xF; //�˲���
   TIM_ICInit(TIM3,&TIM_ICInitStructure); //��ʼ������Ƚϵ�Ԫ
   
   TIM_ICInitStructure.TIM_Channel=TIM_Channel_2; //ͨ��2
   TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //�����ز���
   TIM_ICInitStructure.TIM_ICFilter=0xF; //�˲���
   TIM_ICInit(TIM3,&TIM_ICInitStructure); //��ʼ������Ƚϵ�Ԫ

   //���ñ������ӿ�ģʽ
   TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising); //�������ӿ�ģʽ
   TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
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