#ifndef _PWM_H
#define _PWM_H

void PWM_Init(void);
void PWM_SetPrescaler(uint16_t Prescaler);
void PWM_SetCompare1(uint16_t Compare);
/*
PWM_SetPrescaler(720-1);//Freq=72M/(PSC+1)/100
PWM_SetCompare1(1);//Duty=CCR/100
*/
#endif