#include"stm32f10x.h"
 





// void SPI_W_SS(uint8_t bitValue)
// {
//     GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)bitValue);
// }

// void SPI_W_SCK(uint8_t bitValue)
// {
//     GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)bitValue);
// }


// void SPI_W_MOSI(uint8_t bitValue)
// {
//     GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)bitValue);
// }

// uint8_t SPI_R_MISO(void)
// {
//     return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
// }




// void SoftSPI_Init(void)
// {
// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
// GPIO_InitTypeDef GPIO_InitStructure;
// GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;
// GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
// GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
// GPIO_Init(GPIOA,&GPIO_InitStructure);
// GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
// GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
// GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
// GPIO_Init(GPIOA,&GPIO_InitStructure);

// SPI_W_SS(1);
// SPI_W_SCK(0);
// }

// void SPI_Start(void)
// {
//     SPI_W_SS(0);
// }

// void SPI_Stop(void)
// {
//     SPI_W_SS(1);
// }

// uint8_t SPI_SwapByte(uint8_t ByteSend)
// {
//     uint8_t i, ByteReceive=0x00;
//     for(i=0;i<8;i++)
//     {
//     SPI_W_MOSI(ByteSend&(0x80>>i));
//     SPI_W_SCK(1);
//     if(SPI_R_MISO())
//     {
//         ByteReceive|=(0x80>>i);

//     }
//     SPI_W_SCK(0);
//     }
//     return ByteReceive;
   
// }


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







void SPI_W_SS(uint8_t bitValue)
{
    GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)bitValue);
}




void SoftSPI_Init(void)
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&GPIO_InitStructure);
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_7;
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&GPIO_InitStructure);
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&GPIO_InitStructure);

SPI_InitTypeDef SPI_InitStructure;
SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;  //方向全双工
SPI_InitStructure.SPI_Mode=SPI_Mode_Master;//主机
SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;//8位数据
SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low;//时钟极性
SPI_InitStructure.SPI_CPHA=SPI_CPHA_1Edge;//时钟相位
SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;//NSS软件控制
SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_128;//波特率
SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;//高位先发
SPI_InitStructure.SPI_CRCPolynomial=7;//CRC多项式
SPI_Init(SPI1,&SPI_InitStructure);
SPI_Cmd(SPI1,ENABLE);
 SPI_W_SS(1);
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
   while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)!=SET);
    SPI_I2S_SendData(SPI1,ByteSend);
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)!=SET);
    return SPI_I2S_ReceiveData(SPI1);
}