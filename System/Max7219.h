#ifndef __MAX7219_H
#define __MAX7219_H

#include "stm32f10x.h"


void Max7219_W_CS(uint8_t bitValue);
void Init_MAX7219(void);



void Max7219_GPIO_Init(void);
void Max7219_Init(void);
void Max7219_Write(uint8_t addr,uint8_t dat);
void Max7219_Look(void);

#endif