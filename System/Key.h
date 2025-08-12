#ifndef _KEY_H
#define _KEY_H



#define KEY_HOLD 0x01
#define KEY_DOWN 0x02
#define KEY_UP 0x04
#define KEY_SINGLE 0x08
#define KEY_DOUBLE 0x10
#define KEY_LONG 0x20
#define KEY_REPEAT 0x40
void Key_Init(void);
uint8_t Key_GetNum(void);
void Key_Tick(void);
uint8_t Key_Check(uint8_t Flag);
#endif