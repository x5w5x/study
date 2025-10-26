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

// // ȫ�ֱ���
uint8_t CT[2]; // ������
uint8_t SN[4]; // ����
uint8_t RFID[16];                                      // RFID����
uint8_t key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Ĭ������
// //
// uint8_t status;

// //

// // unsigned char CT[2];//������
// // unsigned char SN[4]; //����
// // unsigned char RFID[16];//���RFID
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
// // SPI��ʼ��
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
 * @brief ����SPI����
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
 * @brief ��ȡSPI����
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
 * @brief ��ȡRC522�Ĵ���
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
//  * @brief дRC�Ĵ���
//  *
//  * @param Address ��ַ
//  * @param Value д���ֵ
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
 * @param Reg ��ַ
 * @param Mask ��ֵλ
 */
void SetMask(uint8_t Reg, uint8_t Mask)
{
    uint8_t Temp;
    Temp = ReadRaw(Reg);
    WriteRaw(Reg, Temp | Mask);
}

/**
 * @brief ���Mask
 *
 * @param Reg ��ַ
 * @param Mask ��ֵλ
 */
void ClearMask(uint8_t Reg, uint8_t Mask)
{

    uint8_t Temp;
    Temp = ReadRaw(Reg);
    WriteRaw(Reg, Temp & (~Mask));
}

/**
 * @brief ��������
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
 * @brief �ر�����
 *
 */
#define PcdAntennaOff() ClearMask(TxControlReg, 0x03);

// /**
//  * @brief ��λ
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
    WriteRaw(ModeReg, 0x3D);       // ���巢�ͺͽ��ճ���ģʽ ��Mifare��ͨѶ��CRC��ʼֵ0x6363
    WriteRaw(TReloadRegL, 30);     // 16λ��ʱ����λ
    WriteRaw(TReloadRegH, 0);      // 16λ��ʱ����λ
    WriteRaw(TModeReg, 0x8D);      // �����ڲ���ʱ��
    WriteRaw(TPrescalerReg, 0x3E); // ���÷�Ƶϵ��
    WriteRaw(TxAutoReg, 0x40);     // ���Ʒ����ź�Ϊ100%ASK
}

/**
 * @brief ���ù�����ʽ
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
 * @brief Ѱ��
 * 
 * @param Command   ����
 * @param InData     �Ĵ�������
 * @param InLen     �Ĵ������ݳ���
 * @param OutData   �Ĵ�������
 * @param OutLen    �Ĵ������ݳ���
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
        case PCD_AUTHENT:   // Mifare��֤
            IrqEn   = 0x12; // ��������ж�����ErrIEn  ��������ж�IdleIEn
            WaitFor = 0x10; // ��֤Ѱ���ȴ�ʱ�� ��ѯ�����жϱ�־λ
            break;

        case PCD_TRANSCEIVE: // ���շ��� ���ͽ���
            IrqEn   = 0x77;  // ����TxIEn RxIEn IdleIEn LoAlertIEn ErrIEn TimerIEn
            WaitFor = 0x30;  // Ѱ���ȴ�ʱ�� ��ѯ�����жϱ�־λ�� �����жϱ�־λ
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
        SetMask(BitFramingReg, 0x80); // StartSend��λ�������ݷ��� ��λ���շ�����ʹ��ʱ����Ч

    l = 1000; // ����ʱ��Ƶ�ʵ���������M1�����ȴ�ʱ��25ms

    do // ��֤ ��Ѱ���ȴ�ʱ��
    {
        N = ReadRaw(ComIrqReg); // ��ѯ�¼��ж�
        l--;
    } while ((l != 0) && (!(N & 0x01)) && (!(N & WaitFor))); // �˳�����i=0,��ʱ���жϣ���д��������

    ClearMask(BitFramingReg, 0x80); // ��������StartSendλ

    if (l != 0) {
        if (!((ReadRaw(ErrorReg) & 0x1B))) // �������־�Ĵ���BufferOfI CollErr ParityErr ProtocolErr
        {
            cStatus = MI_OK;

            if (N & IrqEn & 0x01) // �Ƿ�����ʱ���ж�
                cStatus = MI_NOTAGERR;

            if (Command == PCD_TRANSCEIVE) {
                N = ReadRaw(FIFOLevelReg); // ��FIFO�б�����ֽ���

                LastBits = ReadRaw(ControlReg) & 0x07; // �����յ����ֽڵ���Чλ��

                if (LastBits)
                    *OutLen = (N - 1) * 8 + LastBits; // N���ֽ�����ȥ1�����һ���ֽڣ�+���һλ��λ�� ��ȡ����������λ��
                else
                    *OutLen = N * 8; // �����յ����ֽ������ֽ���Ч

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
 * @brief Ѱ��
 * 
 * @param Req_code  Ѱ����ʽ
 * @param TagType    ������
 * @return int8_t 
 */
int8_t PcdRequest(uint8_t Req_code, uint8_t *TagType)
{
    int8_t cStatus;
    uint8_t ComMF522Buf[MAXRLEN];
    uint32_t lLen;

    ClearMask(Status2Reg, 0x08);   // ����ָʾMIFARECyptol��Ԫ��ͨ�Լ����п�������ͨ�ű����ܵ����
    WriteRaw(BitFramingReg, 0x07); //	���͵����һ���ֽڵ� ��λ
    SetMask(TxControlReg, 0x03);   // TX1,TX2�ܽŵ�����źŴ��ݾ����͵��Ƶ�13.56�������ز��ź�

    ComMF522Buf[0] = Req_code; // ���� ��Ƭ������

    cStatus = PcdComMF522(PCD_TRANSCEIVE, ComMF522Buf, 1, ComMF522Buf, &lLen); // Ѱ��

    if ((cStatus == MI_OK) && (lLen == 0x10)) // Ѱ���ɹ����ؿ�����
    {
        *TagType       = ComMF522Buf[0];
        *(TagType + 1) = ComMF522Buf[1];
    }

    else
        cStatus = MI_ERR;

    return cStatus;
}

/**
 * @brief ����ײ
 *
 * @param Snr ��Ƭ���кţ�4�ֽ�
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
    ComBuf[0] = 0x93; // ��Ƭ����ͻ����
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
 * @brief ��RC522����CRC16
 *
 * @param InData ����CRC16������
 * @param Len ����CRC16�������ֽڳ���
 * @param OutData ��ż�������ŵ��׵�ַ
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
 * @brief ѡ����Ƭ
 *
 * @param Snr ��Ƭ���
 * @return int8_t N״̬
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
 * ��������PcdAuthState
 * ����  ����֤��Ƭ����
 * ����  ��Auth_mode��������֤ģʽ
 *                     = 0x60����֤A��Կ
 *                     = 0x61����֤B��Կ
 *         u8 Addr�����ַ
 *         Key������
 *         Snr����Ƭ���кţ�4�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
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
 * ��������PcdWrite
 * ����  ��д���ݵ�M1��һ��
 * ����  ��Addr�����ַ
 *         Data��д������ݣ�16�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
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
 * ��������PcdRead
 * ����  ����ȡM1��һ������
 * ����  ��u8 ucAddr�����ַ
 *         pData�����������ݣ�16�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
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
 * ��������PcdHalt
 * ����  �����Ƭ��������״̬
 * ����  ����
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
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
 * @brief ��ȡ����
 *
 * @param UID   ����
 * @param KEY    ����
 * @param RW     ��дѡ��1�Ƕ���0��д
 * @param Dat    ����
 */
void IC_CMT(uint8_t *UID, uint8_t *KEY, uint8_t RW, uint8_t *Dat)
{
    uint8_t ucArray_ID[4] = {0}; // �Ⱥ���IC�������ͺ�UID(IC�����к�)

    PcdRequest(0x52, ucArray_ID); // Ѱ��

    PcdAnticoll(ucArray_ID); // ����ײ

    PcdSelect(UID); // ѡ����

    PcdAuthState(0x60, 0x10, KEY, UID); // У��

    if (RW) // ��дѡ��1�Ƕ���0��д
        PcdRead(0x10, Dat);

    else
        PcdWrite(0x10, Dat);

    PcdHalt();
}
/**
 * @brief ��ʾ����
 *
 * @param p ����
 */
void ShowID(uint8_t *p) // ��ʾ���Ŀ��ţ���ʮ��������ʾ
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
 * @brief    �ȴ����뿪
 *
 */
void WaitCardOff(void)
{
    char cstatus;
    while (1) {
        cstatus = PcdRequest(PICC_REQALL, CT); // Ѱ��
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
 * @brief ��ʼ��
 *
 */
void RC522_Init(void)
{
    SPI1_Init();

    RC522_Reset_Disable();

    RC522_CS_Disable();

    PcdReset();
    PcdConfigISOType('A'); // ���ù�����ʽ
}

/*ȫ�ֱ���*/
// unsigned char CT[2];    // ������
// unsigned char SN[4];    // ����
// unsigned char RFID[16]; // ���RFID
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

//     status = PcdRequest(PICC_REQALL, CT); // Ѱ��

//     // printf("\r\nstatus>>>>>>%d\r\n", status);
//     Serial_Printf("\r\nstatus>>>>>>%d\r\n", status);
//     if (status == MI_OK) // Ѱ���ɹ�
//     {
//         status = MI_ERR;
//         status = PcdAnticoll(SN); // ����ײ
//         if (status == MI_OK)      // ����ײ�ɹ�
//         {
//             status = MI_ERR;
//             Serial_Printf("******************************************\r\n");
//             ShowID(SN); // ���ڴ�ӡ����ID��

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
//             if (status == MI_OK) // ѡ���ɹ�
//             {
//                 status = MI_ERR;
//                 status = PcdAuthState(0x60, 0x07, KEY, SN);
//                 if (status == MI_OK) // keyA��֤�ɹ�
//                 {
//                     status = MI_ERR;
//                     status = PcdRead(4, RFID);
//                     if (status == MI_OK) // �����ɹ�
//                     {
//                         blance = RFID[0] * 16 + RFID[1];
//                         if (blance == 0) {
//                             RFID[0] = Recharge / 16;
//                             RFID[1] = Recharge % 16;
//                             status  = MI_ERR;
//                             status  = PcdWrite(4, RFID);
//                             if (status == MI_OK) Serial_Printf(">>>�ɹ���ֵ%dԪ��\r\n", Recharge);
//                             // if(status==MI_OK) printf(">>>Chong zhi Success: %d Y��\r\n",Recharge);
//                             for (char i = 0; i < 2; i++) {
//                             }
//                         } else {
//                             status  = MI_ERR;
//                             RFID[0] = (blance - 1) / 16;
//                             RFID[1] = (blance - 1) % 16;
//                             status  = PcdWrite(4, RFID);
//                             if (status == MI_OK) // д���ɹ�
//                             {
//                                 status = PcdRead(4, RFID);
//                                 if (status == MI_OK) {
//                                     Serial_Printf(">>>>>>ˢ���ɹ���\r\n");
//                                     blance = RFID[0] * 16 + RFID[1];
//                                     Serial_Printf(">>>>>>��%d\r\n", blance);
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


//�÷�

