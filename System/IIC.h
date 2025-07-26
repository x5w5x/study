#ifndef _IIC_H
#define _IIC_H
void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_SendByte(uint8_t Byte);
uint8_t IIC_ReadByte(void);
void IIC_SendAck(uint8_t AckBit);
uint8_t IIC_ReadAck(void);
#endif