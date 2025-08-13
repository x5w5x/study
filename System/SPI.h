#ifndef _SPI_H_
#define _SPI_H_

void SoftSPI_Init(void);
void SPI_Start(void);
void SPI_Stop(void);
uint8_t SPI_SwapByte(uint8_t ByteSend);
#endif /* _SPI_H_ */
