#ifndef _MPU6050_H
#define _ MPU6050_H
void MPU6050_WriteReg(uint8_t reg,uint8_t data);
uint8_t MPU6050_ReadReg(uint8_t reg);
uint8_t MPU6050_GetID(void);
void MPU6050_Init(void);
void MPU6050_GetData(int16_t *AccX,int16_t *AccY,int16_t *AccZ,int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ);
#endif /* _MPU6050_H */