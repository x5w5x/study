#include"stm32f10x.h"
 





void SPI_W_SS(uint8_t bitValue)
{
    GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)bitValue);
}

void SPI_W_SCK(uint8_t bitValue)
{
    GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)bitValue);
}


void SPI_W_MOSI(uint8_t bitValue)
{
    GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)bitValue);
}

uint8_t SPI_R_MISO(void)
{
    return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}




void SoftSPI_Init(void)
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&GPIO_InitStructure);
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&GPIO_InitStructure);

SPI_W_SS(1);
SPI_W_SCK(0);
}

void SPI_Start(void)
{
    SPI_W_SS(0);
}

void SPI_Stop(void)
{
    SPI_W_SS(1);
}

uint8_t SPI_SwapByte(uint8_t ByteSend)
{
    uint8_t i, ByteReceive=0x00;
    for(i=0;i<8;i++)
    {
    SPI_W_MOSI(ByteSend&(0x80>>i));
    SPI_W_SCK(1);
    if(SPI_R_MISO())
    {
        ByteReceive|=(0x80>>i);

    }
    SPI_W_SCK(0);
    }
    return ByteReceive;
   
}


/*
//ģʽ1

uint8_t SPI_SwapByte(uint8_t ByteSend)
{
    uint8_t i, ByteReceive=0x00;
    for(i=0;i<8;i++)
    {
    SPI_W_SCK(1);
    SPI_W_MOSI(ByteSend&(0x80>>i));
    SPI_W_SCK(0);
    if(SPI_R_MISO())
    {
        ByteReceive|=(0x80>>i);

    }
    }
    return ByteReceive;
   
}

*/




