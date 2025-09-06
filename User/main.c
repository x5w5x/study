
#include "stm32f10x.h" 
#include "Delay.h"
#include "led.h"
#include "Key.h"
// #include"Buzzer.h"
// #include"LightSensor.h"
#include "OLED.h"
// #include "CountSensor.h"
// #include "Encoder.h"
// #include"Timer.h"
// #include"pwm.h"
// #include"Serov.h"
// #include"IC.h"
// #include"AD.h"
// #include"DMA.h"
// #include"Serial.h"
#include"W25Q64.h"
#include"mpu6050.h"
// #include"BKP.h"
// #include"RTC.h"
// #include"FLASH.h"
// #include"Store.h"
// #include"OLED2.h"
// #include"OLED_Font.h"
#include "Hanlder.h"
// uint8_t keynum;
// int16_t num=5;
#include"Max7219.h"
#include"ws2812b.h"
int main(void)
{	


      OLED_Init();

      OLED_Clear();
   
WS2812_Init();
for(uint16_t i=1;i<=64;i++){
    WS2812_SetColor(i,1,1,1);
    WS2812_Update();
    Delay_ms(100);
    //  WS2812_SetColor(i-1,0,0,0);
    // WS2812_Update();
}

    // WS2812_SetColor(64,10,10,10);
    // WS2812_Update();








 while(1) {

      
    }
}



	

