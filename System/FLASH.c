#include"stm32f10x.h"


uint32_t FLASH_ReadWord(uint32_t address)
{
    return *((__IO uint32_t*)(address));
}

uint16_t FLASH_ReadHalfWord(uint32_t address)
{
    return *((__IO uint16_t*)(address));
}

uint8_t FLASH_ReadByte(uint32_t address)
{
    return *((__IO uint8_t*)(address));
}

//全部擦除（自杀式）
void Flash_EraseAllPages(void)
{
    FLASH_Unlock();
    FLASH_EraseAllPages();
    FLASH_Lock();
}
//擦除指定页
void Flash_ErasePage(uint32_t Pageaddress)
{
    FLASH_Unlock();
    FLASH_ErasePage(Pageaddress);
    FLASH_Lock();
}

void Flash_WriteWord(uint32_t address,uint32_t data)
{
    FLASH_Unlock();
    FLASH_ProgramWord(address,data);
    FLASH_Lock();
}
void Flash_WriteHalfWord(uint32_t address,uint16_t data)
{
    FLASH_Unlock();
    FLASH_ProgramHalfWord(address,data);
    FLASH_Lock();
}

