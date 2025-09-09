#ifndef _TIMER_H
#define _TIMER_H

#define TIM2_time 2 //(1-1s 0-1ms 2自定义)



#if TIM2_time==1

#define TIM2_period 10000-1 //计数器周期
#define TIM2_prescaler 7200-1 //预分频系数

#elif TIM2_time==0

#define TIM2_period 1000-1 //计数器周期
#define TIM2_prescaler 72-1 //预分频系数

#elif TIM2_time==2

#define TIM2_period 72-1 //计数器周期
#define TIM2_prescaler 100-1 //预分频系数

#endif 




void Timer_Init(void);
void Timer_ETRInit(void);


#endif