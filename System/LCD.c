#include"stm32f10x.h"
#include"LCD.h"
#include "Delay.h"

void LCD_GPIO_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void SPI_WriteData(uint8_t Data){
uint8_t i;
for(i=0;i<8;i++){
    if(Data &(0x80>>i)){
        LCD_SDA_SET;
    }else{
        LCD_SDA_CLR;
    }
    LCD_SCL_CLR;
    LCD_SCL_SET;
}

}

void LCD_WriteCmd(uint8_t cmd){
    LCD_CS_CLR;
    LCD_RS_CLR;
    SPI_WriteData(cmd);
    LCD_CS_SET;
}
void LCD_WriteData(uint8_t Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   SPI_WriteData(Data);
   LCD_CS_SET; 
}
void LCD_WriteDatas(uint8_t *Data,uint8_t Count){
    uint8_t i;
    LCD_CS_CLR;
    LCD_RS_SET;
    for(i=0;i<Count;i++){
        SPI_WriteData(Data[i]);
    }
    LCD_CS_SET;
}
void LCD_WriteData_16bit(uint16_t Data){
    LCD_CS_CLR;
    LCD_RS_SET;
    SPI_WriteData(Data>>8);
    SPI_WriteData(Data);
    LCD_CS_SET;
}


void LCD_WriteReg(uint8_t cmd,uint8_t Data){
 LCD_WriteCmd(cmd);
    LCD_WriteData(Data);
}
void LCD_Reset(void){
    LCD_RST_CLR;
    Delay_ms(100);
    LCD_RST_SET;
    Delay_ms(50);
   
}

void LCD_Init(void)
{
    LCD_GPIO_Init();
    LCD_Reset();
    LCD_WriteCmd(0x11);
    Delay_ms(120);
    LCD_WriteCmd(0XB1);
    LCD_WriteData(0x01); 
	LCD_WriteData(0x2C); 
	LCD_WriteData(0x2D); 

	LCD_WriteCmd(0xB2); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x2C); 
	LCD_WriteData(0x2D);
    LCD_WriteCmd(0xB3); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x2C); 
	LCD_WriteData(0x2D); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x2C); 
	LCD_WriteData(0x2D); 
	
	LCD_WriteCmd(0xB4);  
	LCD_WriteData(0x07); 

	LCD_WriteCmd(0xC0); 
	LCD_WriteData(0xA2); 
	LCD_WriteData(0x02); 
	LCD_WriteData(0x84); 
	LCD_WriteCmd(0xC1); 
	LCD_WriteData(0xC5); 

	LCD_WriteCmd(0xC2); 
	LCD_WriteData(0x0A); 
	LCD_WriteData(0x00); 

	LCD_WriteCmd(0xC3); 
	LCD_WriteData(0x8A); 
	LCD_WriteData(0x2A); 
	LCD_WriteCmd(0xC4); 
	LCD_WriteData(0x8A); 
	LCD_WriteData(0xEE); 
	
	LCD_WriteCmd(0xC5); 
	LCD_WriteData(0x0E); 
	
	LCD_WriteCmd(0x36);
	LCD_WriteData(0xC0); 
	

	LCD_WriteCmd(0xe0); 
	LCD_WriteData(0x0f); 
	LCD_WriteData(0x1a); 
	LCD_WriteData(0x0f); 
	LCD_WriteData(0x18); 
	LCD_WriteData(0x2f); 
	LCD_WriteData(0x28); 
	LCD_WriteData(0x20); 
	LCD_WriteData(0x22); 
	LCD_WriteData(0x1f); 
	LCD_WriteData(0x1b); 
	LCD_WriteData(0x23); 
	LCD_WriteData(0x37); 
	LCD_WriteData(0x00); 	
	LCD_WriteData(0x07); 
	LCD_WriteData(0x02); 
	LCD_WriteData(0x10); 

	LCD_WriteCmd(0xe1); 
	LCD_WriteData(0x0f); 
	LCD_WriteData(0x1b); 
	LCD_WriteData(0x0f); 
	LCD_WriteData(0x17); 
	LCD_WriteData(0x33); 
	LCD_WriteData(0x2c); 
	LCD_WriteData(0x29); 
	LCD_WriteData(0x2e); 
	LCD_WriteData(0x30); 
	LCD_WriteData(0x30); 
	LCD_WriteData(0x39); 
	LCD_WriteData(0x3f); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x03); 
	LCD_WriteData(0x10);  
	
	LCD_WriteCmd(0x2a);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x7f);

	LCD_WriteCmd(0x2b);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x9f);
	
	LCD_WriteCmd(0xF0); 
	LCD_WriteData(0x01); 
	LCD_WriteCmd(0xF6);  
	LCD_WriteData(0x00); 
	
	LCD_WriteCmd(0x3A); 
	LCD_WriteData(0x05); 
	
	
	LCD_WriteCmd(0x29);  
    LCD_LED_SET;


}

void LCD_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end){
    LCD_WriteCmd(0x2a);
	LCD_WriteData(0x00);
	LCD_WriteData(x_start);
	LCD_WriteData(0x00);
	LCD_WriteData(x_end+2);

	LCD_WriteCmd(0x2b);
	LCD_WriteData(0x00);
	LCD_WriteData(y_start+0);
	LCD_WriteData(0x00);
	LCD_WriteData(y_end+1);
	
	LCD_WriteCmd(0x2c);
}
void LCD_SetXY(uint16_t x,uint16_t y)
{
  	LCD_SetRegion(x,y,x,y);
}

void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data)
{
	LCD_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16bit(Data);

} 

unsigned int Lcd_ReadPoint(uint16_t x,uint16_t y)
{
  unsigned int Data;
  LCD_SetXY(x,y);

  //Lcd_ReadData();//¶ªµôÎÞÓÃ×Ö½Ú
  //Data=Lcd_ReadData();
  LCD_WriteData(Data);
  return Data;
}

void Lcd_Clear(uint16_t Color)               
{	
   unsigned int i,m;
   LCD_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   LCD_WriteCmd(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	LCD_WriteData_16bit(Color);
    }   
}


