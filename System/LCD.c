#include"stm32f10x.h"
#include"LCD.h"
#include "Delay.h"
#include "stdio.h"
#include"LCD_Font.h"



// extern FontDef Font_16x24;
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
//双分支
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

  //Lcd_ReadData();//丢掉无用字节
  //Data=Lcd_ReadData();
  LCD_WriteData(Data);
  return Data;
}

void LCD_Clear(uint16_t Color)               
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


void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color){
	if(x>=LCD_WIDTH||y>=LCD_HEIGTH) return;
	Gui_DrawPoint(x,y,color);
}
//Bresenham算法
void LCD_DrawLine(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t color){
	int dx=x0<x1?x1-x0:x0-x1;
	int dy=y0<y1?y1-y0:y0-y1;
	int sx=x0<x1?1:-1;
	int sy=y0<y1?1:-1;
	int err=dx-dy;
	while(1){
		LCD_DrawPoint(x0,y0,color);
		if(x0==x1&&y0==y1) break;
		int e2=err*2;
		if(e2>-dy){
			err-=dy;
			x0+=sx;
		}
		if(e2<dx){
			err+=dx;
			y0+=sy;
		}
	}
}

/*

	x0,y0--------------x1,y0
    |********************|                   
	|********************|                   
	|********************|                    
	|********************|                    
	x0,y1--------------x1,y1
	
   
*/
void LCD_DrawRectangle(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t color){
	LCD_DrawLine(x0,y0,x1,y0,color);
	LCD_DrawLine(x0,y0,x0,y1,color);
	LCD_DrawLine(x0,y1,x1,y1,color);
	LCD_DrawLine(x1,y0,x1,y1,color);
}


void LCD_DrawFullRectangle(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t color){
	uint16_t i;
	for(i=y0;i<y1;i++)
	LCD_DrawLine(x0,i,x1,i,color);
}
//中心圆算法
void LCD_DrawCircle(uint16_t x0,uint16_t y0,uint16_t r,uint16_t color){
	int f=1-r;
	int ddf_x=1;
	int ddf_y= -2*r;
	int x=0;
	int y=r;
	//四个基准点
	LCD_DrawPoint(x0,y0+r,color);
	LCD_DrawPoint(x0,y0-r,color);
	LCD_DrawPoint(x0+r,y0,color);
	LCD_DrawPoint(x0-r,y0,color);
	while(x<y){
		if(f>=0){
			y--;
			ddf_y+=2;
			f+=ddf_y;
		}
		x++;
		ddf_x+=2;
		f+=ddf_x;
		LCD_DrawPoint(x0 + x, y0 + y, color);
        LCD_DrawPoint(x0 - x, y0 + y, color);
        LCD_DrawPoint(x0 + x, y0 - y, color);
        LCD_DrawPoint(x0 - x, y0 - y, color);
        LCD_DrawPoint(x0 + y, y0 + x, color);
        LCD_DrawPoint(x0 - y, y0 + x, color);
        LCD_DrawPoint(x0 + y, y0 - x, color);
        LCD_DrawPoint(x0 - y, y0 - x, color);
	}

}



void LCD_DrawFilledCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color) {
    int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x = 0;
    int y = r;

    LCD_DrawLine(x0, y0 + r, x0, y0 - r, color);
    LCD_DrawPoint(x0 + r, y0, color);
    LCD_DrawPoint(x0 - r, y0, color);

    while(x < y) {
        if(f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        
        LCD_DrawLine(x0 + x, y0 + y, x0 + x, y0 - y, color);
        LCD_DrawLine(x0 - x, y0 + y, x0 - x, y0 - y, color);
        LCD_DrawLine(x0 + y, y0 + x, x0 + y, y0 - x, color);
        LCD_DrawLine(x0 - y, y0 + x, x0 - y, y0 - x, color);
    }
}



void LCD_PutChar(uint16_t x, uint16_t y, char c, FontDef font, uint16_t color, uint16_t bgcolor) {
    uint32_t i, j, b;
    
    for(i = 0; i < font.height; i++) {
        b = font.data[(c - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if((b << j) & 0x80) {
                LCD_DrawPoint(x + j, y + i, color);
            } else {
                LCD_DrawPoint(x + j, y + i, bgcolor);
            }
        }
    }
}



void LCD_PutString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor) {
    while(*str) {
        LCD_PutChar(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }
}

//内存占用大
// void LCD_PrintNum(uint16_t x, uint16_t y, uint32_t num, FontDef font, uint16_t color, uint16_t bgcolor) {
//     char buf[12];
//     sprintf(buf, "%lu", num);
//     LCD_PutString(x, y, buf, font, color, bgcolor);
// }


// void LCD_PrintHex(uint16_t x, uint16_t y, uint32_t num, FontDef font, uint16_t color, uint16_t bgcolor) {
//     char buf[10];
//     sprintf(buf, "0x%lX", num);
//     LCD_PutString(x, y, buf, font, color, bgcolor);
// }


// void LCD_PrintFloat(uint16_t x, uint16_t y, float num, uint8_t decimals, FontDef font, uint16_t color, uint16_t bgcolor) {
//     char buf[20];
//     char format[10];
    
//     sprintf(format, "%%.%df", decimals);
//     sprintf(buf, format, num);
//     LCD_PutString(x, y, buf, font, color, bgcolor);
// }
