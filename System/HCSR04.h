#ifndef _HCSR04_H_
#define _HCSR04_H_

#include "stm32f10x.h"

// void HCSR04_Init(void);
// void HCSR04_Start(void);
void HCSR04_Init(void);
float HCSR04_GetDistance(void);

#endif /* _HCSR04_H_ */