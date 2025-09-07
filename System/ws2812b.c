#include"ws2812b.h"
#include"Delay.h"


#if WS2812_MODE==1


uint8_t Color[WS2812_NUM][24];
void WS2812_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Cmd(SPI1, ENABLE);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Color;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = 24*WS2812_NUM;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel3, &DMA_InitStructure);

    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
    DMA_Cmd(DMA1_Channel3, DISABLE);
for(uint8_t i=0;i<WS2812_NUM;i++){
    for(uint8_t j=0;j<24;j++){
        Color[i][j]=0xE0;
    }
    
}
}

void WS2812_SetColor(uint8_t n,uint8_t r,uint8_t g,uint8_t b){
        uint8_t i;
        for(i=0;i<8;i++){
            if(g&(0x80>>i))
            Color[n-1][i]=0xF8;
            else
            Color[n-1][i]=0xE0;
            if(r&(0x80>>i))
            Color[n-1][i+8]=0xF8;
            else
            Color[n-1][i+8]=0xE0;
            if(b&(0x80>>i))
            Color[n-1][i+16]=0xF8;
            else
            Color[n-1][i+16]=0xE0;
        }
    }
void WS2812_Update(void){
    DMA_Cmd(DMA1_Channel3, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel3,24*WS2812_NUM);
    DMA_Cmd(DMA1_Channel3, ENABLE);

    while(DMA_GetFlagStatus(DMA1_FLAG_TC3)==RESET);
    DMA_ClearFlag(DMA1_FLAG_TC3);

}



#elif WS2812_MODE==2

uint16_t Color[WS2812_NUM][24];
void WS2812_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    DMA_InitTypeDef DMA_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseStructure.TIM_Period = 8-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 8-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);


    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_Cmd(TIM2, ENABLE);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&TIM2->CCR1;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Color;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = 24*WS2812_NUM;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);

    DMA_Cmd(DMA1_Channel5, DISABLE);
    TIM_DMACmd(TIM2, TIM_DMA_CC1, ENABLE);

    for(uint8_t i=0;i<WS2812_NUM;i++){
    for(uint8_t j=0;j<24;j++){
        Color[i][j]=2;
    }
    
}
}
void WS2812_SetColor(uint8_t n,uint8_t r,uint8_t g,uint8_t b){
    
        uint8_t i;
        for(i=0;i<8;i++){
            if(g&(0x80>>i))
            Color[n-1][i]=6;
            else
            Color[n-1][i]=2;
            if(r&(0x80>>i))
            Color[n-1][i+8]=6;
            else
            Color[n-1][i+8]=2;
            if(b&(0x80>>i))
            Color[n-1][i+16]=6;
            else
            Color[n-1][i+16]=2;
        }
}

void WS2812_Update(void){
    DMA_SetCurrDataCounter(DMA1_Channel5,WS2812_NUM * 24);
	DMA_Cmd(DMA1_Channel5,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	while(DMA_GetFlagStatus(DMA1_FLAG_TC5) != SET);
	DMA_ClearFlag(DMA1_FLAG_TC5);
    
    TIM_SetCompare1(TIM2,0);                        
	DMA_Cmd(DMA1_Channel5,DISABLE);
	TIM_Cmd(TIM2,DISABLE);

}

 
#else

uint8_t Color[WS2812_NUM][3]={0};

void WS2812_Spi_SendByte(uint8_t byte){
    SPI_I2S_SendData(SPI1,byte);
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);
}
#define WS2812_Send0 WS2812_Spi_SendByte(0xE0) //0码
#define WS2812_Send1 WS2812_Spi_SendByte(0xF8) //1码

void WS2812_SendByte(uint8_t byte){
    uint8_t i;
    for(i=0;i<8;i++){
        if(byte>>7)
            WS2812_Send1;
        else 
            WS2812_Send0;
        byte<<=1;
    }
}

void WS2812_Send24bit(uint8_t r,uint8_t g,uint8_t b){
    WS2812_SendByte(g);
    WS2812_SendByte(r);
    WS2812_SendByte(b);
}
void WS2812_SetColor(uint8_t n,uint8_t r,uint8_t g,uint8_t b){
    Color[n-1][0]=r;
    Color[n-1][1]=g;
    Color[n-1][2]=b;
}
void WS2812_Update(void){
    uint8_t i;
    for(i=0;i<WS2812_NUM;i++){
        WS2812_Send24bit(Color[i][0],Color[i][1],Color[i][2]);
    }
}
void WS2812_Init(void){

    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Cmd(SPI1, ENABLE);

}

#endif

void WS2812_Clear(void)
{
    uint8_t i;
    for(i=0;i<WS2812_NUM;i++){
        Color[i][0]=0;
        Color[i][1]=0;
        Color[i][2]=0;
    }
    WS2812_Update();
}
void WS2812_Hex(uint8_t Hex,uint8_t n,uint8_t r,uint8_t g,uint8_t b){
for(uint8_t i=8;i>=1;i--){
  if(Hex&(1<<(i-1))) WS2812_SetColor(8*n-i+1,r,g,b);
  else WS2812_SetColor(8*n-i+1,0,0,0);
}
}
//二维数组
/*
    uint8_t hex[10][8]={
0x00,0x18,0x66,0x42,0x42,0x42,0x3C,0x00,

0x00,0x08,0x18,0x08,0x08,0x08,0x18,0x00,

0x00,0x3C,0x42,0x06,0x08,0x30,0x7E,0x00,

0x00,0x38,0x46,0x04,0x0C,0x42,0x7C,0x00,

0x00,0x04,0x1C,0x24,0x44,0x3C,0x0C,0x00,

0x00,0x00,0x7C,0x7C,0x02,0x42,0x7C,0x00,

0x00,0x18,0x64,0x5C,0x62,0x42,0x3C,0x00,

0x00,0x00,0x7C,0x08,0x08,0x10,0x10,0x00,

0x00,0x3C,0x42,0x72,0x4C,0x42,0x7C,0x00,

0x00,0x3C,0x42,0x42,0x7E,0x02,0x7C,0x00,
};
*/
void WS2812_HexArr(uint8_t *Hex,uint8_t n,uint8_t r,uint8_t g,uint8_t b)
{
for(uint8_t i=1;i<=n;i++){
  WS2812_Hex(Hex[i-1],i,r,g,b);
}
}

//一维数组
/*

    uint8_t arr[]={

        
0x00,0x18,0x66,0x42,0x42,0x42,0x3C,0x00,

0x00,0x08,0x18,0x08,0x08,0x08,0x18,0x00,

0x00,0x3C,0x42,0x06,0x08,0x30,0x7E,0x00,

0x00,0x38,0x46,0x04,0x0C,0x42,0x7C,0x00,

0x00,0x04,0x1C,0x24,0x44,0x3C,0x0C,0x00,

0x00,0x00,0x7C,0x7C,0x02,0x42,0x7C,0x00,

0x00,0x18,0x64,0x5C,0x62,0x42,0x3C,0x00,

0x00,0x00,0x7C,0x08,0x08,0x10,0x10,0x00,

0x00,0x3C,0x42,0x72,0x4C,0x42,0x7C,0x00,

0x00,0x3C,0x42,0x42,0x7E,0x02,0x7C,0x00,
};
*/
void WS2812_HexSC(uint8_t *Hex,uint8_t n,uint8_t r,uint8_t g,uint8_t b)
{
for(uint8_t j=0;j<72;j++)
for(uint8_t i=1;i<=n;i++){
  WS2812_Hex(Hex[i-1+j],i,r,g,b);
//   WS2812_Hex(Hex[i-1+j],i,rgb[j][0],rgb[j][1],rgb[j][2]);

  WS2812_Update();
  Delay_ms(10);
}
}