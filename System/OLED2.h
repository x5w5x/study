#ifndef _OLED2_H
#define _OLED2_H

void OLED_Init(void);
void OLED_WriteData(uint8_t data);
void OLED_SetCursor(uint8_t x, uint8_t y);

#endif /* _OLED2_H */