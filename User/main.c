
#include "stm32f10x.h" 
#include "Delay.h"
#include "led.h"
#include "Key.h"
// #include"Buzzer.h"
// #include"LightSensor.h"
#include "OLED.h"
#include "CountSensor.h"
// #include "Encoder.h"
// #include"Timer.h"
// #include"pwm.h"
#include"Serov.h"
// #include"IC.h"
#include"AD.h"
// #include"DMA.h"
// #include"Serial.h"
// #include"W25Q64.h"
// #include"mpu6050.h"
// #include"BKP.h"
// #include"RTC.h"
// #include"FLASH.h"
// #include"Store.h"
// #include"OLED2.h"
// #include"OLED_Font.h"
// #include "Hanlder.h"
// uint8_t keynum;
// int16_t num=5;
// #include"Max7219.h"
// #include"ws2812b.h"
// #include"HCSR04.h"
#include"LCD.h"
/*
*/
//上下90（45居中）
//左右180（90居中）
//pa4 x 稳定值：2040+-10 最大值：4095 最小值：0000
//pa5 y 稳定值: 2056+-10 最大值：4095 最小值：0000
extern FontDef Font_8x16;
uint8_t num;
float x,y,x_pid,y_pid,x_ang,y_ang;
int main(void)
{   			
    Servo_Init();
    // Servo1_SetAngle(5);
	// CountSensor_Init();
// LED_Init();
// LED_On(1);
// LED_On(2);
	
// LCD_Init();
// Lcd_Init();

// Lcd_Clear(RED);  
// LCD_SetRegion(5,5,20,20);
//  Delay_ms(1000);
//  LCD_Clear(WHITE);
 
// LCD_DrawPoint(10,10,BLACK);
//  LCD_DrawLine(10,10,50,100,BLACK);
//  LCD_DrawRectangle(10,10,50,50,BLACK);
//  LCD_DrawFullRectangle(10,10,50,50,BLACK);
// LCD_DrawCircle(50,50,20,BLACK);
// LCD_DrawFilledCircle(50,50,20,BLACK);
//  LCD_ShowChar(1,1,'A',Font_8x16,RED,WHITE);
///LCD_PutChar(0,0,'!',Font_8x16,BLACK,RED);

// LCD_PutString(10, 10, "Hello World!", Font_8x16, BLACK,  YELLOW);
// LCD_PrintNum(10, 30, 12345, Font_8x16, GREEN, BLACK);
// LCD_PrintFloat(10, 50, 3.14159, 3, Font_8x16, RED, BLACK);

//
//初始化
    AD_Init();
    OLED_Init();
    OLED_Clear();
    OLED_ShowString(1,1,"Hello World!");
 while(1) {
// num=Get_state();
// 	OLED_ShowNum(2,1,num,1);
    x=AD_Value[0];
    y=AD_Value[1];
    x_pid=x-2040;
    y_pid=y-2056;

	OLED_ShowNum(3,1,x,4);
if(x_pid<0){x_pid=(x_pid/2040)*45;}
else x_pid=(x_pid/2055)*45;
//上2039 下2055
if(y_pid<0){y_pid=(y_pid/2056)*90;}
else y_pid=(y_pid/2039)*90;
//左2039 右2056
    // OLED_ShowNum(3,6,45+x_pid,4);
    OLED_ShowNum(4,1,y,4);
    // OLED_ShowNum(4,6,90+y_pid,4);
    if(45+x_pid<90||45+x_pid>0)
    x_ang=45+x_pid;
    else if(45+x_pid>=90)x_ang=90;
    else x_ang=0;
 if(90+y_pid<90||90+y_pid>0)
    y_ang=90+y_pid;
    else if(90+y_pid>=180)y_ang=180;
    else y_ang=0;
    
    OLED_ShowNum(3,6,x_ang,4);
    OLED_ShowNum(4,6,y_ang,4);


     Servo1_SetAngle(x_ang);
     Servo2_SetAngle(y_ang);
    // Delay_s(1);
	
    }

}



    
