#ifndef _OLED2_H
#define _OLED2_H

void OLED_Init(void);
void OLED_WriteData(uint8_t data);
void OLED_SetCursor(uint8_t x, uint8_t y);
void OLED_On(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size);
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *str, uint8_t size);
void OLED_ShowImage(uint8_t x, uint8_t y, uint8_t width, uint8_t height,const uint8_t *Image);
void OLED_GRAM_Fill(void);
void OLED_GRAM_Clear(void);
void OLED_DrawPoint(uint8_t x, uint8_t y);
void OLED_ClearPoint(uint8_t x, uint8_t y);
void OLED_UpdateGRAM(void);
void FourPoint(uint8_t x,uint8_t y);
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t dot);
void OLED_ClearLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t dot);
void OLED_DrawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void OLED_DrawBlock(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void OLED_ADCWavePoint(uint8_t step);
void OLED_ADCWaveLine(uint8_t step);
void OLED_DrawSin( uint8_t x0,uint8_t y0);
void OLED_DrawCircle(uint8_t x0,uint8_t y0,uint8_t r);
void OLED_ClearCircle(uint8_t x0,uint8_t y0,uint8_t r);
void OLED_DrawElliptic(uint8_t x0,uint8_t y0,uint8_t a,uint8_t b);
//
// void ButtonWave(void);
#endif /* _OLED2_H */