#ifndef _TIMER_H
#define _TIMER_H

#define TIM2_time 2 //(1-1s 0-1ms 2�Զ���)



#if TIM2_time==1

#define TIM2_period 10000-1 //����������
#define TIM2_prescaler 7200-1 //Ԥ��Ƶϵ��

#elif TIM2_time==0

#define TIM2_period 1000-1 //����������
#define TIM2_prescaler 72-1 //Ԥ��Ƶϵ��

#elif TIM2_time==2

#define TIM2_period 72-1 //����������
#define TIM2_prescaler 100-1 //Ԥ��Ƶϵ��

#endif 




void Timer_Init(void);
void Timer_ETRInit(void);


#endif