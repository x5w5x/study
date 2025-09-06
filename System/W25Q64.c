#include"stm32f10x.h"
#include"SPI.h"
#include"W25Q64_Ins.h"
/**
 * @brief   ��ʼ��W25Q64
 * @note ����: SPI1 SCK->PA5  MISO(Do)->PA6  MOSI(DI)->PA7  CS->PA4
 * 
 */
void W25Q64_Init(void)
{
SoftSPI_Init();
}
/**
 * @brief   ��ȡW25Q64��ID
 * 
 * @param MID  ������ID
 * @param DID �豸ID
 */
void W25Q64_ReadID(uint8_t *MID,uint16_t *DID)
{
    SPI_Start();
    SPI_SwapByte(W25Q64_JEDEC_ID);
    *MID=SPI_SwapByte(W25Q64_DUMMY_BYTE);
    *DID=SPI_SwapByte(W25Q64_DUMMY_BYTE);
    *DID<<=8;
    *DID|=SPI_SwapByte(W25Q64_DUMMY_BYTE);

}


void W26Q64_WriteEnable(void)
{
    SPI_Start();
    SPI_SwapByte(W25Q64_WRITE_ENABLE);
    SPI_Stop();
}

void W25Q64_WaitBusy(void)
{
    SPI_Start();
    SPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
    while(SPI_SwapByte(W25Q64_DUMMY_BYTE)&0x01);
    SPI_Stop();
}

/**
 * @brief   ҳд��
 * 
 * @param addr  д���ַ
 * @param data   д������
 * @param len    д�볤��
 */
void W25Q64_PageProgram(uint32_t addr,uint8_t *data,uint16_t len)
{
    W26Q64_WriteEnable();
    SPI_Start();
    SPI_SwapByte(W25Q64_PAGE_PROGRAM);
    SPI_SwapByte((addr>>16)&0xFF);
    SPI_SwapByte((addr>>8)&0xFF);
    SPI_SwapByte(addr&0xFF);
    while(len--)
    {
        SPI_SwapByte(*data++);

    }
    SPI_Stop();
    W25Q64_WaitBusy();
}
/**
 * @brief   ��������
 * 
 * @param addr  ������ַ
 */
void W25Q64_SectorErase(uint32_t addr)
{
    W26Q64_WriteEnable();
    SPI_Start();
    SPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
    SPI_SwapByte((addr>>16)&0xFF);
    SPI_SwapByte((addr>>8)&0xFF);
    SPI_SwapByte(addr&0xFF);
    SPI_Stop();
    W25Q64_WaitBusy();
}
/**
 * @brief   32KB�����
 * 
 * @param addr  ������ַ
 */
void W25Q64_BlockErase(uint32_t addr)
{
    SPI_Start();
    SPI_SwapByte(W25Q64_BLOCK_ERASE_32KB);
    SPI_SwapByte((addr>>16)&0xFF);
    SPI_SwapByte((addr>>8)&0xFF);
    SPI_SwapByte(addr&0xFF);
    SPI_Stop();
}
/**
 * @brief   ��Ƭ����
 * 
 */
void W25Q64_ChipErase(void)
{
    SPI_Start();
    SPI_SwapByte(W25Q64_CHIP_ERASE);
    SPI_Stop();
}
/**
 * @brief   ��ȡW25Q64������
 * 
 * @param addr  ��ȡ��ַ
 * @param data  ��ȡ����
 * @param len    ��ȡ����
 */
void W25Q64_ReadData(uint32_t addr,uint8_t *data,uint16_t len)
{
    SPI_Start();
    SPI_SwapByte(W25Q64_READ_DATA);
    SPI_SwapByte((addr>>16)&0xFF);
    SPI_SwapByte((addr>>8)&0xFF);
    SPI_SwapByte(addr&0xFF);
    while(len--)
    {
        *data++=SPI_SwapByte(W25Q64_DUMMY_BYTE);
    }
}
