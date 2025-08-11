
#include "stm32f10x.h" 
#include "Delay.h"
#include "led.h"
#include "Key.h"
// #include"Buzzer.h"
// #include"LightSensor.h"
#include "OLED.h"
// #include "CountSensor.h"
// #include "Encoder.h"
#include"Timer.h"
// #include"pwm.h"
// #include"Serov.h"
// #include"IC.h"
// #include"AD.h"
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
#include "Hanlder.h"

uint8_t keynum;
#include"Max7219.h"

int main(void)
{	
LED_Init();
Key_Init();
Timer_Init();
OLED_Init();

OLED_Clear();


	while(1){

        keynum=Key_GetNum();
	if(keynum==1)
    // LED_On(1);
     LED_Set(led_turn);
   

    if(keynum==2)
     LED_Set(led_flash);
        


}}



	

