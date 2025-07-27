#ifndef _W25Q64_H_
#define _W25Q64_
void W25Q64_Init(void);
void W25Q64_ReadID(uint8_t *MID,uint16_t *DID);
void W25Q64_PageProgram(uint32_t addr,uint8_t *data,uint16_t len);
void W25Q64_SectorErase(uint32_t addr);
void W25Q64_ReadData(uint32_t addr,uint8_t *data,uint16_t len);
#endif /* _W25Q64_H_ */