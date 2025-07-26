#ifndef _MPU6050_REG_H_
#define _MPU6050_REG_H_


#define	MPU6050_SMPLRT_DIV		0x19 //�����ʷ�Ƶ��
#define	MPU6050_CONFIG			0x1A //��ͨ�˲���
#define	MPU6050_GYRO_CONFIG		0x1B //����������
#define	MPU6050_ACCEL_CONFIG	0x1C //���ٶȼ�����

#define	MPU6050_ACCEL_XOUT_H	0x3B //���ٶȼ�X��߰�λ
#define	MPU6050_ACCEL_XOUT_L	0x3C //���ٶȼ�X��Ͱ�λ
#define	MPU6050_ACCEL_YOUT_H	0x3D //���ٶȼ�Y��߰�λ
#define	MPU6050_ACCEL_YOUT_L	0x3E //���ٶȼ�Y��Ͱ�λ
#define	MPU6050_ACCEL_ZOUT_H	0x3F //���ٶȼ�Z��߰�λ
#define	MPU6050_ACCEL_ZOUT_L	0x40 //���ٶȼ�Z��Ͱ�λ
#define	MPU6050_TEMP_OUT_H		0x41 //�¶�ֵ�߰�λ
#define	MPU6050_TEMP_OUT_L		0x42 //�¶�ֵ�Ͱ�λ
#define	MPU6050_GYRO_XOUT_H		0x43 //������X��߰�λ
#define	MPU6050_GYRO_XOUT_L		0x44 //������X��Ͱ�λ
#define	MPU6050_GYRO_YOUT_H		0x45 //������Y��߰�λ
#define	MPU6050_GYRO_YOUT_L		0x46 //������Y��Ͱ�λ
#define	MPU6050_GYRO_ZOUT_H		0x47 //������Z��߰�λ
#define	MPU6050_GYRO_ZOUT_L		0x48 //������Z��Ͱ�λ

#define	MPU6050_PWR_MGMT_1		0x6B //��Դ����
#define	MPU6050_PWR_MGMT_2		0x6C //��Դ����
#define	MPU6050_WHO_AM_I		0x75 //�豸ID




#endif /* _MPU6050_REG_H_ */