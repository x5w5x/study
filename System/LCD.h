#ifndef  _LCD_H_
#define _LCD_H_

/*
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PA5��SCL��
//              SDA   ��PA7��SDA��
//              RES   ��PB0
//              DC    ��PB1
//              CS    ��PA4 
//				BL	  ��PB10
*/


//


#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        160
//��ɫ
#define RED 0xf800
#define GREEN 0x07e0
#define BLUE 0x001f
#define WHITE 0xffff
#define BLACK 0x0000
#define YELLOW 0xFFE0
#define GRAY0 0xEF7D
#define GRAY1 0x8410
#define GRAY2 0x4208
//�˿�
#define LCD_CTRLA  GPIOB
#define LCD_CCTRLB GPIOB
//����
#define LCD_SCL GPIO_Pin_13
#define LCD_SDA GPIO_Pin_14
#define LCD_CS GPIO_Pin_5

#define LCD_LED GPIO_Pin_6
#define LCD_RS GPIO_Pin_7
#define LCD_RST GPIO_Pin_12

//�궨��
#define LCD_SCL_SET LCD_CTRLA->BSRR=LCD_SCL
#define LCD_SDA_SET  LCD_CTRLA->BSRR=LCD_SDA
#define LCD_CS_SET  LCD_CTRLA->BSRR=LCD_CS

#define LCD_LED_SET  LCD_CTRLA->BSRR=LCD_LED
#define LCD_RS_SET  LCD_CTRLA->BSRR=LCD_RS
#define LCD_RST_SET  LCD_CTRLA->BSRR=LCD_RST

#define LCD_SCL_CLR LCD_CTRLA->BRR=LCD_SCL
#define LCD_SDA_CLR  LCD_CTRLA->BRR=LCD_SDA
#define LCD_CS_CLR   LCD_CTRLA->BRR=LCD_CS

#define LCD_LED_CLR   LCD_CTRLA->BRR=LCD_LED
#define LCD_RS_CLR   LCD_CTRLA->BRR=LCD_RS
#define LCD_RST_CLR   LCD_CTRLA->BRR=LCD_RST
//����
#define LCD_DATAOUT(x) LCD_DATA->ODR=x;
#define LCD_DATA_IN LCD_DATA->ODR;

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
}



void LCD_Init(void);
void LCD_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);
void Lcd_Clear(uint16_t Color);
#endif // ! 