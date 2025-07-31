#ifndef _FLASH_H
#define _FLASH_H

uint32_t FLASH_ReadWord(uint32_t address);
uint16_t FLASH_ReadHalfWord(uint32_t address);
uint8_t FLASH_ReadByte(uint32_t address);
void Flash_EraseAllPages(void);
void Flash_ErasePage(uint32_t Pageaddress);
void Flash_WriteWord(uint32_t address,uint32_t data);
void Flash_WriteHalfWord(uint32_t address,uint16_t data);
void Flash_WriteByte(uint32_t address,uint8_t data);
#endif /* _FLASH_H */