#ifndef _SPI_H_
#define _SPI_H_

#define SPI_MODE 1 //0:Ӳ��SPI 1:���SPI

void SoftSPI_Init(void);
void SPI_Start(void);
void SPI_Stop(void);
uint8_t SPI_SwapByte(uint8_t ByteSend);
#endif /* _SPI_H_ */
