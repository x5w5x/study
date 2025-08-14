#ifndef _SEROV_H
#define _SEROV_H


void Servo_Init(void);
void Servo1_SetAngle(float angle);
void Servo2_SetAngle(float angle);
void Servo3_SetAngle(float angle);
void Servo4_SetAngle(float angle);
void Servo_SetAngle(uint8_t servo,float angle);
#endif