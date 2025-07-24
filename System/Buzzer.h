#ifndef _BUZZER_H
#define _BUZZER_H

// #define Buzzer_On() GPIO_ResetBits(GPIOB, GPIO_Pin_12);
void Buzzer_Init(void);
void Buzzer_On(void);
void Buzzer_Off(void);
void Buzzer_Turn(void);

#endif