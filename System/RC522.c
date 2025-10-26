// /*
//  * @Author: xwx
//  * @Date: 2025-10-17 20:12:45
//  * @LastEditTime: 2025-10-25 18:10:10
//  * @FilePath: \learn\System\RC522.c
//  */
#include "RC522.h"
#include "stm32f10x.h"
#include "delay.h"
#include "string.h"
#include "stdio.h"
#include "Serial.h"

// // 全局变量
uint8_t CT[2]; // 卡类型
uint8_t SN[4]; // 卡号
uint8_t RFID[16];                                      // RFID卡号
uint8_t key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // 默认密码
// //
// uint8_t status;

// //

// // unsigned char CT[2];//卡类型
// // unsigned char SN[4]; //卡号
// // unsigned char RFID[16];//存放RFID
// unsigned char card1_bit=0;
// unsigned char card2_bit=0;
// unsigned char card3_bit=0;
// unsigned char card4_bit=0;
// unsigned char card_1[4]= {103,92,120,137};
// unsigned char card_2[4]= {244,42,180,115};
// unsigned char card_3[4]= {128,233,142,167};
// unsigned char card_4[4]= {166,67,153,172};
// // u8 KEY[6]= {0xff,0xff,0xff,0xff,0xff,0xff};
// u8 AUDIO_OPEN[6] = {0xAA, 0x07, 0x02, 0x00, 0x09, 0xBC};
// unsigned char RFID1[16]= {0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};
// unsigned char status;
// unsigned char s=0x08;
// int blance;
#define RC522_DELAY() Delay_us(2)
// // SPI初始化
void SPI1_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin   = RCC_SDA_PIN | RCC_SCK_PIN | RCC_MOSI_PIN | RCC_RST_PIN;
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

// /**
//  * @brief 写RC寄存器
//  *
//  * @param Address 地址
//  * @param Value 写入的值
//  */
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

// /**
//  * @brief 复位
//  *
//  */
void PcdReset(void)
{
    RC522_Reset_Disable();
    Delay_us(2);
    RC522_Reset_Enable();
    Delay_us(2);
    RC522_Reset_Disable();
    Delay_us(2);
    WriteRaw(CommandReg, 0x0f);
    while (ReadRaw(CommandReg) & 0x10);
    Delay_us(2);
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
/**
 * @brief 寻卡
 * 
 * @param Command   命令
 * @param InData     寄存器数据
 * @param InLen     寄存器数据长度
 * @param OutData   寄存器数据
 * @param OutLen    寄存器数据长度
 * @return int8_t 
 */
int8_t PcdComMF522(uint8_t Command, uint8_t *InData, uint8_t InLen, uint8_t *OutData, uint32_t *OutLen)
{
    //
    int8_t cStatus  = MI_ERR;
    uint8_t IrqEn   = 0x00;
    uint8_t WaitFor = 0x00;
    uint8_t LastBits;
    uint8_t N;
    uint32_t l;

    switch (Command) {
        case PCD_AUTHENT:   // Mifare认证
            IrqEn   = 0x12; // 允许错误中断请求ErrIEn  允许空闲中断IdleIEn
            WaitFor = 0x10; // 认证寻卡等待时候 查询空闲中断标志位
            break;

        case PCD_TRANSCEIVE: // 接收发送 发送接收
            IrqEn   = 0x77;  // 允许TxIEn RxIEn IdleIEn LoAlertIEn ErrIEn TimerIEn
            WaitFor = 0x30;  // 寻卡等待时候 查询接收中断标志位与 空闲中断标志位
            break;

        default:
            break;
    }
    WriteRaw(ComIEnReg, IrqEn | 0x80);
    ClearMask(ComIrqReg, 0x80);
    WriteRaw(CommandReg, PCD_IDLE);
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
/**
 * @brief 寻卡
 * 
 * @param Req_code  寻卡方式
 * @param TagType    卡类型
 * @return int8_t 
 */
int8_t PcdRequest(uint8_t Req_code, uint8_t *TagType)
{
    int8_t cStatus;
    uint8_t ComMF522Buf[MAXRLEN];
    uint32_t lLen;

    ClearMask(Status2Reg, 0x08);   // 清理指示MIFARECyptol单元接通以及所有卡的数据通信被加密的情况
    WriteRaw(BitFramingReg, 0x07); //	发送的最后一个字节的 七位
    SetMask(TxControlReg, 0x03);   // TX1,TX2管脚的输出信号传递经发送调制的13.56的能量载波信号

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

/**
 * @brief 防冲撞
 *
 * @param Snr 卡片序列号，4字节
 * @return int8_t
 */
int8_t PcdAnticoll(uint8_t *Snr)
{
    int8_t Status;
    uint8_t i, Snr_check = 0;
    uint8_t ComBuf[MAXRLEN];
    uint32_t len;
    ClearMask(Status2Reg, 0x08);
    WriteRaw(BitFramingReg, 0x00);
    ClearMask(ControlReg, 0x80);
    ComBuf[0] = 0x93; // 卡片防冲突命令
    ComBuf[1] = 0x20;
    Status    = PcdComMF522(PCD_TRANSCEIVE, ComBuf, 2, ComBuf, &len);
    if (Status == MI_OK) {
        for (i = 0; i < 4; i++) {
            *(Snr + i) = ComBuf[i];
            Snr_check ^= ComBuf[i];
        }
        if (Snr_check != ComBuf[i])
            Status = MI_ERR;
    }
    SetMask(CollReg, 0x80);

    return Status;
}
/**
 * @brief 用RC522计算CRC16
 *
 * @param InData 计算CRC16的数组
 * @param Len 计算CRC16的数组字节长度
 * @param OutData 存放计算结果存放的首地址
 */
void CalulateCRC(uint8_t *InData, uint8_t Len, uint8_t *OutData)
{
    uint8_t i, N;
    ClearMask(DivIrqReg, 0x04);
    WriteRaw(CommandReg, PCD_IDLE);
    SetMask(FIFOLevelReg, 0x80);
    for (i = 0; i < Len; i++)
        WriteRaw(FIFODataReg, *(InData + i));
    WriteRaw(CommandReg, PCD_CALCCRC);
    i = 0xFF;
    do {
        N = ReadRaw(DivIrqReg);
        i--;
    } while ((i != 0) && !(N & 0x04));
    OutData[0] = ReadRaw(CRCResultRegL);
    OutData[1] = ReadRaw(CRCResultRegM);
}
/**
 * @brief 选定卡片
 *
 * @param Snr 卡片序号
 * @return int8_t N状态
 */
int8_t PcdSelect(uint8_t *Snr)
{
    int8_t N;
    uint8_t i;
    uint8_t ComBuf[MAXRLEN];
    uint32_t Len;
    ComBuf[0] = PICC_ANTICOLL1;
    ComBuf[1] = 0x70;
    ComBuf[2] = 0;
    for (i = 0; i < 4; i++) {
        ComBuf[i + 2] = *(Snr + i);
        ComBuf[6] ^= *(Snr + i);
    }
    CalulateCRC(ComBuf, 7, &ComBuf[7]);
    ClearMask(Status2Reg, 0x08);
    N = PcdComMF522(PCD_TRANSCEIVE, ComBuf, 9, ComBuf, &Len);
    if ((N == MI_OK) && (Len == 0x18))
        N = MI_OK;
    else
        N = MI_ERR;
    return N;
}

/*
 * 函数名：PcdAuthState
 * 描述  ：验证卡片密码
 * 输入  ：Auth_mode，密码验证模式
 *                     = 0x60，验证A密钥
 *                     = 0x61，验证B密钥
 *         u8 Addr，块地址
 *         Key，密码
 *         Snr，卡片序列号，4字节
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用
 */
int8_t PcdAuthState(uint8_t Auth_mode, uint8_t Addr, uint8_t *Key, uint8_t *Snr)
{
    int8_t Status;
    uint8_t i, ComBuf[MAXRLEN];
    uint32_t Len;
    ComBuf[0] = Auth_mode;
    ComBuf[1] = Addr;

    for (i = 0; i < 6; i++) {
        ComBuf[i + 2] = *(Key + i);
        ComBuf[i + 8] = *(Snr + i);
    }

    // for(i=0;i<6;i++)
    //     ComBuf[i+8]=*(Snr+i);
    Status = PcdComMF522(PCD_AUTHENT, ComBuf, 12, ComBuf, &Len);
    if ((Status != MI_OK) || (!(ReadRaw(Status2Reg) & 0x08)))
        Status = MI_ERR;
    return Status;
}

/*
 * 函数名：PcdWrite
 * 描述  ：写数据到M1卡一块
 * 输入  ：Addr，块地址
 *         Data，写入的数据，16字节
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用
 */
int8_t PcdWrite(uint8_t Addr, uint8_t *Data)
{
    int8_t Status;
    uint8_t i, ComBuf[MAXRLEN];
    uint32_t Len;

    ComBuf[0] = PICC_WRITE;
    ComBuf[1] = Addr;

    CalulateCRC(ComBuf, 2, &ComBuf[2]);

    Status = PcdComMF522(PCD_TRANSCEIVE, ComBuf, 4, ComBuf, &Len);

    if ((Status != MI_OK) || (Len != 4) || ((ComBuf[0] & 0x0F) != 0x0A))
        Status = MI_ERR;

    if (Status == MI_OK) {
        memcpy(ComBuf, Data, 16);
        for (i = 0; i < 16; i++)
            ComBuf[i] = *(Data + i);

        CalulateCRC(ComBuf, 16, &ComBuf[16]);

        Status = PcdComMF522(PCD_TRANSCEIVE, ComBuf, 18, ComBuf, &Len);

        if ((Status != MI_OK) || (Len != 4) || ((ComBuf[0] & 0x0F) != 0x0A))
            Status = MI_ERR;
    }
    return Status;
}

/*
 * 函数名：PcdRead
 * 描述  ：读取M1卡一块数据
 * 输入  ：u8 ucAddr，块地址
 *         pData，读出的数据，16字节
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用
 */
int8_t PcdRead(uint8_t Addr, uint8_t *Data)
{
    int8_t Status;
    uint8_t i, ComBuf[MAXRLEN];
    uint32_t Len;

    ComBuf[0] = PICC_READ;
    ComBuf[1] = Addr;

    CalulateCRC(ComBuf, 2, &ComBuf[2]);

    Status = PcdComMF522(PCD_TRANSCEIVE, ComBuf, 4, ComBuf, &Len);

    if ((Status == MI_OK) && (Len == 0x90)) {
        for (i = 0; i < 16; i++)
            *(Data + i) = ComBuf[i];
    }

    else
        Status = MI_ERR;

    return Status;
}

/*
 * 函数名：PcdHalt
 * 描述  ：命令卡片进入休眠状态
 * 输入  ：无
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用
 */
int8_t PcdHalt(void)
{
    uint8_t ComBuf[MAXRLEN];
    uint32_t Len;

    ComBuf[0] = PICC_HALT;
    ComBuf[1] = 0;

    CalulateCRC(ComBuf, 2, &ComBuf[2]);
    PcdComMF522(PCD_TRANSCEIVE, ComBuf, 4, ComBuf, &Len);

    return MI_OK;
}

/**
 * @brief 读取卡号
 *
 * @param UID   卡号
 * @param KEY    密码
 * @param RW     读写选择，1是读，0是写
 * @param Dat    数据
 */
void IC_CMT(uint8_t *UID, uint8_t *KEY, uint8_t RW, uint8_t *Dat)
{
    uint8_t ucArray_ID[4] = {0}; // 先后存放IC卡的类型和UID(IC卡序列号)

    PcdRequest(0x52, ucArray_ID); // 寻卡

    PcdAnticoll(ucArray_ID); // 防冲撞

    PcdSelect(UID); // 选定卡

    PcdAuthState(0x60, 0x10, KEY, UID); // 校验

    if (RW) // 读写选择，1是读，0是写
        PcdRead(0x10, Dat);

    else
        PcdWrite(0x10, Dat);

    PcdHalt();
}
/**
 * @brief 显示卡号
 *
 * @param p 卡号
 */
void ShowID(uint8_t *p) // 显示卡的卡号，以十六进制显示
{
  uint8_t num[9];
    uint8_t i;

    for (i = 0; i < 4; i++) {
        num[i * 2] = p[i] / 16;
        num[i * 2] > 9 ? (num[i * 2] += '7') : (num[i * 2] += '0');
        num[i * 2 + 1] = p[i] % 16;
        num[i * 2 + 1] > 9 ? (num[i * 2 + 1] += '7') : (num[i * 2 + 1] += '0');
    }
    num[8] = 0;
    Serial_Printf("IC_ID>>>%s\r\n", num);
}

/**
 * @brief    等待卡离开
 *
 */
void WaitCardOff(void)
{
    char cstatus;
    while (1) {
        cstatus = PcdRequest(PICC_REQALL, CT); // 寻卡
        if (cstatus) {
            cstatus = PcdRequest(PICC_REQALL, CT);
            if (cstatus) {
                cstatus = PcdRequest(PICC_REQALL, CT);
                if (cstatus) {
                    cstatus = PcdRequest(PICC_REQALL, CT);
                    if (cstatus) return;
                }
            }
        }
        Delay_ms(100);
    }
}
/**
 * @brief 初始化
 *
 */
void RC522_Init(void)
{
    SPI1_Init();

    RC522_Reset_Disable();

    RC522_CS_Disable();

    PcdReset();
    PcdConfigISOType('A'); // 设置工作方式
}

/*全局变量*/
// unsigned char CT[2];    // 卡类型
// unsigned char SN[4];    // 卡号
// unsigned char RFID[16]; // 存放RFID
// unsigned char card1_bit = 0;
// unsigned char card2_bit = 0;
// unsigned char card3_bit = 0;
// unsigned char card4_bit = 0;
// unsigned char card_1[4] = {103, 92, 120, 137};
// unsigned char card_2[4] = {244, 42, 180, 115};
// unsigned char card_3[4] = {128, 233, 142, 167};
// unsigned char card_4[4] = {166, 67, 153, 172};
// u8 KEY[6]               = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
// u8 AUDIO_OPEN[6]        = {0xAA, 0x07, 0x02, 0x00, 0x09, 0xBC};
// unsigned char RFID1[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x07, 0x80, 0x29, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
// unsigned char status;
// unsigned char s = 0x08;
// int blance;

// void RC522_Handel(void)
// {

//     status = PcdRequest(PICC_REQALL, CT); // 寻卡

//     // printf("\r\nstatus>>>>>>%d\r\n", status);
//     Serial_Printf("\r\nstatus>>>>>>%d\r\n", status);
//     if (status == MI_OK) // 寻卡成功
//     {
//         status = MI_ERR;
//         status = PcdAnticoll(SN); // 防冲撞
//         if (status == MI_OK)      // 防冲撞成功
//         {
//             status = MI_ERR;
//             Serial_Printf("******************************************\r\n");
//             ShowID(SN); // 串口打印卡的ID号

//             if ((SN[0] == card_1[0]) && (SN[1] == card_1[1]) && (SN[2] == card_1[2]) && (SN[3] == card_1[3])) {
//                 card1_bit = 1;
//                 Serial_Printf("User>>>CARD_1\r\n");
//             }
//             if ((SN[0] == card_2[0]) && (SN[1] == card_2[1]) && (SN[2] == card_2[2]) && (SN[3] == card_2[3])) {
//                 card2_bit = 1;
//                 Serial_Printf("User>>>CARD_2\r\n");
//             }
//             if ((SN[0] == card_3[0]) && (SN[1] == card_3[1]) && (SN[2] == card_3[2]) && (SN[3] == card_3[3])) {
//                 card3_bit = 1;
//                 Serial_Printf("User>>>CARD_3\r\n");
//             }
//             if ((SN[0] == card_4[0]) && (SN[1] == card_4[1]) && (SN[2] == card_4[2]) && (SN[3] == card_4[3])) {
//                 card4_bit = 1;
//                 Serial_Printf("User>>>CARD_4\r\n");
//             }
//             // total=card1_bit+card2_bit+card3_bit+card4_bit+lxl_bit;
//             status = PcdSelect(SN);
//             if (status == MI_OK) // 选卡成功
//             {
//                 status = MI_ERR;
//                 status = PcdAuthState(0x60, 0x07, KEY, SN);
//                 if (status == MI_OK) // keyA验证成功
//                 {
//                     status = MI_ERR;
//                     status = PcdRead(4, RFID);
//                     if (status == MI_OK) // 读卡成功
//                     {
//                         blance = RFID[0] * 16 + RFID[1];
//                         if (blance == 0) {
//                             RFID[0] = Recharge / 16;
//                             RFID[1] = Recharge % 16;
//                             status  = MI_ERR;
//                             status  = PcdWrite(4, RFID);
//                             if (status == MI_OK) Serial_Printf(">>>成功充值%d元！\r\n", Recharge);
//                             // if(status==MI_OK) printf(">>>Chong zhi Success: %d Y！\r\n",Recharge);
//                             for (char i = 0; i < 2; i++) {
//                             }
//                         } else {
//                             status  = MI_ERR;
//                             RFID[0] = (blance - 1) / 16;
//                             RFID[1] = (blance - 1) % 16;
//                             status  = PcdWrite(4, RFID);
//                             if (status == MI_OK) // 写卡成功
//                             {
//                                 status = PcdRead(4, RFID);
//                                 if (status == MI_OK) {
//                                     Serial_Printf(">>>>>>刷卡成功！\r\n");
//                                     blance = RFID[0] * 16 + RFID[1];
//                                     Serial_Printf(">>>>>>余额：%d\r\n", blance);
//                                 }
//                                 status = MI_ERR;
//                                 Delay_ms(100);
//                             }
//                         }
//                     }
//                 }
//             }
//             Serial_Printf("******************************************\r\n\r\n");
//             WaitCardOff();
//         }
//     }

//     else {
//         Serial_Printf("No Card..\n");
//     }
// }


//用法

