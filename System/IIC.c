#include"stm32f10x.h"   
#include"Delay.h"
/**
 * @breif: IIC��ʼ�ź�
 * @param: ��
 */
void IIC_W_SCL(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)BitValue);
    Delay_us(10);
}
/**
 * @breif: IICֹͣ�ź�
 */
void IIC_W_SDA(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_11,(BitAction)BitValue);
    Delay_us(10);
}
/**
 * @breif: IIC��ȡSDA���ŵ�ƽ
 */
uint8_t IIC_R_SDA(void)
{
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    Delay_us(10);
    return BitValue;
}
/*
1.SCl��SDA��������Ϊ��©���
2.SCA��SDA�øߵ�ƽ


*/

/**
 * @brief   : IIC��ʼ��
 * @param    : ��
 * @retval   : ��
 * @note     : ����SCL-->PB10��SDA-->PB11
 * 
 * 
 */
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_10|GPIO_Pin_11);

}

void IIC_Start(void)
{
IIC_W_SDA(1);
IIC_W_SCL(1);
IIC_W_SDA(0);
IIC_W_SCL(0);
}

void IIC_Stop(void)
{
    IIC_W_SDA(0);
    IIC_W_SCL(1);
    IIC_W_SDA(1);
}

void IIC_SendByte(uint8_t Byte)
{
    uint8_t i;
    for(i=0;i<8;i++)
    {
        IIC_W_SDA(Byte&0x80);
        Byte<<=1;
        IIC_W_SCL(1);
        IIC_W_SCL(0);
    }

    
}
   

uint8_t IIC_ReadByte(void)
{
    uint8_t i,Byte=0;
    IIC_W_SDA(1);
    for(i=0;i<8;i++)
    {
        IIC_W_SCL(1);
        
        if(IIC_R_SDA())
        {
            Byte|=(0x80 >> i);
            
        }
        IIC_W_SCL(0);
    }
    return Byte;

}

void IIC_SendAck(uint8_t AckBit)
{
    IIC_W_SCL(0);
    IIC_W_SDA(AckBit);
    IIC_W_SCL(1);
    IIC_W_SCL(0);
    
}

uint8_t IIC_ReadAck(void)
{
    uint8_t AckBit;
    IIC_W_SCL(0);
    IIC_W_SDA(1);
    IIC_W_SCL(1);
    AckBit = IIC_R_SDA();
    IIC_W_SCL(0);
    return AckBit;
}