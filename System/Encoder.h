#ifndef _ENCODER_H
#define _ENCODER_H
#define ENCODER_MODE 1 // 0：编码器计时器接口模式 1：编码器中断接口模式

void Encoder_Init(void);
int16_t Encoder_Get(void);


#endif // _ENCODER_H