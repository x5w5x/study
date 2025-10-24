/*
 * @Author: xwx
 * @Date: 2025-10-17 20:12:45
 * @LastEditTime: 2025-10-24 22:07:33
 * @FilePath: \learn\System\RC522.c
 */
#include "RC522.h"
#include "stm32f10x.h"
#include "delay.h"
#include "string.h"
#include "stdio.h"
#include "Serial.h"

// 全局变量
uint8_t CT[2];                                         // 卡类型
uint8_t SN[4];                                         // 卡号
uint8_t RFID[16];                                      // RFID卡号
uint8_t KEY[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // 默认密码
//
uint8_t status;

//
#define RC522_DELAY() Delay_ms(2)
// SPI初始化
void SPI1_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin   = RCC_SDA_PIN | RCC_RST_PIN | RCC_MOSI_PIN | RCC_RST_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RCC_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = RCC_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
}

/**
 * @brief 发送SPI数据
 *
 * @param byte
 */
void SPI_RC522_SendByte(uint8_t byte)
{

    for (int i = 0; i < 8; i++) {
        if (byte & 0x80)
            RC522_MOSI_1();
        else
            RC522_MOSI_0();
        RC522_DELAY();
        RC522_SCK_0();
        RC522_DELAY();
        RC522_SCK_1();
        RC522_DELAY();
        byte <<= 1;
    }
}

/**
 * @brief 读取SPI数据
 *
 * @return uint8_t
 */
uint8_t SPI_ReadByte(void)
{
    uint8_t SPI_Data;
    for (int i = 0; i < 8; i++) {
        SPI_Data <<= 1;
        RC522_SCK_0();
        RC522_DELAY();
        if (RC522_MISO_GET() == 1)
            SPI_Data |= 0x01;
        RC522_DELAY();
        RC522_SCK_1();
        RC522_DELAY();
    }
    return SPI_Data;
}
/**
 * @brief 读取RC522寄存器
 *
 * @param ucAddress
 * @return uint8_t
 */
uint8_t ReadRaw(uint8_t Address)
{
    uint8_t Addr, Return;
    Addr = ((Address << 1) & 0x7E) | 0x80;
    RC522_CS_Enable();
    SPI_RC522_SendByte(Addr);
    Return = SPI_ReadByte();
    RC522_CS_Disable();
    return Return;
}
/**
 * @brief 写RC寄存器
 *
 * @param Address 地址
 * @param Value 写入的值
 */
void WriteRaw(uint8_t Address, uint8_t Value)
{
    uint8_t Addr;
    Addr = (Address << 1) & 0x7E;
    RC522_CS_Enable();
    SPI_RC522_SendByte(Addr);
    SPI_RC522_SendByte(Value);
    RC522_CS_Disable();
}
/**
 * @brief Set the Bit Mask object
 *
 * @param Reg 地址
 * @param Mask 清值位
 */
void SetMask(uint8_t Reg, uint8_t Mask)
{
    uint8_t Temp;
    Temp = ReadRaw(Reg);
    WriteRaw(Reg, Temp | Mask);
}

/**
 * @brief 清除Mask
 *
 * @param Reg 地址
 * @param Mask 清值位
 */
void ClearMask(uint8_t Reg, uint8_t Mask)
{

    uint8_t Temp;
    Temp = ReadRaw(Reg);
    WriteRaw(Reg, Temp & (~Mask));
}

/**
 * @brief 开启天线
 *
 */
void PcdAntennaOn(void)
{
    uint8_t Temp;
    Temp = ReadRaw(TxControlReg);
    if (!(Temp & 0x03))
        SetMask(TxControlReg, 0x03);
}

// void PcdAntennaOff(void){
//     ClearMask(TxControlReg,0x03);
// }
/**
 * @brief 关闭天线
 *
 */
#define PcdAntennaOff() ClearMask(TxControlReg, 0x03);

/**
 * @brief 复位
 *
 */
void PcdReset(void)
{
    RC522_Reset_Disable();
    Delay_ms(2);
    RC522_Reset_Enable();
    Delay_ms(2);
    RC522_Reset_Disable();
    Delay_ms(2);
    WriteRaw(CommandReg, 0x0f);
    while (ReadRaw(CommandReg) & 0x10);
    Delay_ms(2);
    WriteRaw(ModeReg, 0x3D);       // 定义发送和接收常用模式 和Mifare卡通讯，CRC初始值0x6363
    WriteRaw(TReloadRegL, 30);     // 16位定时器低位
    WriteRaw(TReloadRegH, 0);      // 16位定时器高位
    WriteRaw(TModeReg, 0x8D);      // 定义内部定时器
    WriteRaw(TPrescalerReg, 0x3E); // 设置分频系数
    WriteRaw(TxAutoReg, 0x40);     // 调制发送信号为100%ASK
}

/**
 * @brief 设置工作方式
 *
 * @param Type
 */
void PcdConfigISOType(uint8_t Type)
{
    if (Type == 'A') {
        ClearMask(Status2Reg, 0x08);

        WriteRaw(ModeReg, 0x3D);

        WriteRaw(RxSelReg, 0x86);

        WriteRaw(RFCfgReg, 0x7F);

        WriteRaw(TReloadRegL, 30);

        WriteRaw(TReloadRegH, 0);

        WriteRaw(TModeReg, 0x8D);

        WriteRaw(TPrescalerReg, 0x3E);

        Delay_us(2);

        PcdAntennaOn();
    }
}

int8_t PcdComMF522(uint8_t Command, uint8_t *InData, uint8_t InLen, uint8_t *OutData, uint32_t *OutLen)
{
    int8_t cStatus  = MI_ERR;
    uint8_t IrqEn   = 0x00;
    uint8_t WaitFor = 0x00;
    uint8_t LastBits;
    uint8_t N;
    uint32_t l;

    switch (Command) {
        case PCD_AUTHENT:
            IrqEn   = 0x12;
            WaitFor = 0x10;
            break;
        case PCD_TRANSCEIVE:
            IrqEn   = 0x77;
            WaitFor = 0x30;
        default:
            break;
    }

    WriteRaw(ComIEnReg, IrqEn | 0x80);
    ClearMask(ComIEnReg, 0x80);
    WriteRaw(Command, PCD_IDLE);
    SetMask(FIFOLevelReg, 0x80);

    for (l = 0; l < InLen; l++) {
        WriteRaw(FIFODataReg, InData[l]);
    }
    WriteRaw(CommandReg, Command);

    if (Command == PCD_TRANSCEIVE)
        SetMask(BitFramingReg, 0x80); // StartSend置位启动数据发送 该位与收发命令使用时才有效

    l = 1000; // 根据时钟频率调整，操作M1卡最大等待时间25ms

    do // 认证 与寻卡等待时间
    {
        N = ReadRaw(ComIrqReg); // 查询事件中断
        l--;
    } while ((l != 0) && (!(N & 0x01)) && (!(N & WaitFor))); // 退出条件i=0,定时器中断，与写空闲命令

    ClearMask(BitFramingReg, 0x80); // 清理允许StartSend位

    if (l != 0) {
        if (!((ReadRaw(ErrorReg) & 0x1B))) // 读错误标志寄存器BufferOfI CollErr ParityErr ProtocolErr
        {
            cStatus = MI_OK;

            if (N & IrqEn & 0x01) // 是否发生定时器中断
                cStatus = MI_NOTAGERR;

            if (Command == PCD_TRANSCEIVE) {
                N = ReadRaw(FIFOLevelReg); // 读FIFO中保存的字节数

                LastBits = ReadRaw(ControlReg) & 0x07; // 最后接收到得字节的有效位数

                if (LastBits)
                    *OutLen = (N - 1) * 8 + LastBits; // N个字节数减去1（最后一个字节）+最后一位的位数 读取到的数据总位数
                else
                    *OutLen = N * 8; // 最后接收到的字节整个字节有效

                if (N == 0)
                    N = 1;

                if (N > MAXRLEN)
                    N = MAXRLEN;

                for (l = 0; l < N; l++)
                    OutData[l] = ReadRaw(FIFODataReg);
            }
        } else
            cStatus = MI_ERR;
    }

    SetMask(ControlReg, 0x80); // stop timer now
    WriteRaw(CommandReg, PCD_IDLE);

    return cStatus;
}

char PcdRequest(uint8_t Req_code, uint8_t *TagType)
{
    int8_t cStatus;
    uint8_t ComMF522Buf[MAXRLEN];
    uint32_t lLen;

    ClearMask(Status2Reg, 0x08);  // 清理指示MIFARECyptol单元接通以及所有卡的数据通信被加密的情况
    WriteRaw(BitFramingReg, 0x07); //	发送的最后一个字节的 七位
    SetMask(TxControlReg, 0x03);  // TX1,TX2管脚的输出信号传递经发送调制的13.56的能量载波信号

    ComMF522Buf[0] = Req_code; // 存入 卡片命令字

    cStatus = PcdComMF522(PCD_TRANSCEIVE, ComMF522Buf, 1, ComMF522Buf, &lLen); // 寻卡

    if ((cStatus == MI_OK) && (lLen == 0x10)) // 寻卡成功返回卡类型
    {
        *TagType       = ComMF522Buf[0];
        *(TagType + 1) = ComMF522Buf[1];
    }

    else
        cStatus = MI_ERR;

    return cStatus;
}