#ifndef _OLED2_H
#define _OLED2_H

void OLED_Init(void);
void OLED_WriteData(uint8_t data);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size);
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *str, uint8_t size);
void OLED_ShowImage(uint8_t x, uint8_t y, uint8_t width, uint8_t height,const uint8_t *Image);
#endif /* _OLED2_H */