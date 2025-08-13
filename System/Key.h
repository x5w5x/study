#ifndef _KEY_H
#define _KEY_H

#define KEY_MODE 1 //0 -阻塞模式 1 -非阻塞模式


#define KEY_HOLD 0x01
#define KEY_DOWN 0x02
#define KEY_UP 0x04
#define KEY_SINGLE 0x08
#define KEY_DOUBLE 0x10
#define KEY_LONG 0x20
#define KEY_REPEAT 0x40

#define KEY_1 0
#define KEY_2 1
#define KEY_3 2
#define KEY_4 3
void Key_Init(void);

#if KEY_MODE
uint8_t Key_Check(uint8_t n, uint8_t Flag);
void Key_Tick(void);
#else 
uint8_t Key_GetNum(void);

#endif








// uint8_t Key_Check(uint8_t Flag);

#endif