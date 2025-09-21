
#include "stm32f10x.h" 
#include "Delay.h"
#include "led.h"
#include "Key.h"
// #include"Buzzer.h"
// #include"LightSensor.h"
// #include "OLED.h"
#include "CountSensor.h"
// #include "Encoder.h"
// #include"Timer.h"
// #include"pwm.h"
// #include"Serov.h"
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


extern FontDef Font_8x16;
uint8_t num;
int main(void)
{   			
	// CountSensor_Init();
// LED_Init();
// LED_On(1);
// LED_On(2);
	// AD_Init();
    //   OLED_Init();

    //   OLED_Clear();
    //   OLED_ShowString(1,1,"Hello World!");
LCD_Init();
// Lcd_Init();

// Lcd_Clear(RED);  
// LCD_SetRegion(5,5,20,20);
//  Delay_ms(1000);
 LCD_Clear(WHITE);
 
// LCD_DrawPoint(10,10,BLACK);
//  LCD_DrawLine(10,10,50,100,BLACK);
//  LCD_DrawRectangle(10,10,50,50,BLACK);
//  LCD_DrawFullRectangle(10,10,50,50,BLACK);
LCD_DrawCircle(50,50,20,BLACK);
// LCD_DrawFilledCircle(50,50,20,BLACK);
//  LCD_ShowChar(1,1,'A',Font_8x16,RED,WHITE);
LCD_PutChar(0,0,'!',Font_8x16,BLACK,RED);

LCD_PutString(10, 10, "Hello STM32!", Font_8x16, BLACK,  YELLOW);
// LCD_PrintNum(10, 30, 12345, Font_8x16, GREEN, BLACK);
// LCD_PrintFloat(10, 50, 3.14159, 3, Font_8x16, RED, BLACK);
 while(1) {
// num=Get_state();
// 	OLED_ShowNum(2,1,num,1);
	// OLED_ShowNum(3,1,AD_Value[0],4);
	
    }

}



    
