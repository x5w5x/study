#ifndef _TIMER_H
#define _TIMER_H

#define TIM2_time 0 //(1-1s 0-1ms)



#if TIM2_time

#define TIM2_period 10000-1 //����������
#define TIM2_prescaler 7200-1 //Ԥ��Ƶϵ��

#else

#define TIM2_period 1000-1 //����������
#define TIM2_prescaler 72-1 //Ԥ��Ƶϵ��

#endif 




void Timer_Init(void);
void Timer_ETRInit(void);


#endif