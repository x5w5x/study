#ifndef _WS2812B_H
#define _WS2812B_H

#include"stm32f10x.h"

#define WS2812_MODE 0 //(0:SPI 1:SPI+DMA 1.5k 2:PWM+DMA 3k) 设置通信方式
#define WS2812_NUM  64 //灯珠数量



void WS2812_SetColor(uint8_t n, uint8_t r, uint8_t g, uint8_t b);
void WS2812_Update(void);
void WS2812_Init(void);
#endif /* _WS2812B_H */

