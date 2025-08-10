#ifndef __MAX7219_H
#define __MAX7219_H

#include "stm32f10x.h"

/* 引脚定义（保持原样）*/
#define Max7219_pinDIN_GPIO GPIO_Pin_7
#define Max7219_pinCS_GPIO  GPIO_Pin_3
#define Max7219_pinCLK_GPIO GPIO_Pin_5
#define SPI_MISO_GPIO       GPIO_Pin_6

/* 使用标准库的GPIO操作替代原sys.h的PAout() */
#define Max7219_pinDIN (GPIOA->ODR & GPIO_Pin_7) ? 1 : 0
#define Max7219_pinCS  (GPIOA->ODR & GPIO_Pin_3) ? 1 : 0
#define Max7219_pinCLK (GPIOA->ODR & GPIO_Pin_5) ? 1 : 0

/* 函数声明（保持原样）*/
void Max7219_GPIO_Init(void);
void Write_Max7219_byte(u8 data);
void Write_Max7219(u8 addr,u8 dat);
void Init_MAX7219(void);

#endif