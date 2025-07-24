#ifndef _SERIAL_H
#define _SERIAL_H
// #include"stdio.h"
void Serial_Init(void);
void Serial_SendByte(uint8_t byte);
void Serial_SendArray(uint8_t *array,uint16_t len);
void Serial_SendString(char *str);
void Serial_SendNum(uint32_t num);
void Serial_Printf(char *fmt,...);
uint8_t Serial_GetRxData(void);
uint8_t Serial_GetFlag(void);
#endif // !_SERIAL_H
