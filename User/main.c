
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
#include"AD.h"
#include"DMA.h"
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
int16_t num=5;
#include"Max7219.h"

int main(void)
{	
      AD_Init();
      OLED_Init();
      // LED_Init();

      // Key_Init();
      OLED_Clear();

      

    
       
     

     



      
     


	while(1){
         OLED_ShowNum(1,1,AD_Value[0],5);
         OLED_ShowNum(2,1,AD_Value[1],5);
         OLED_ShowNum(3,1,AD_Value[2],5);
         OLED_ShowNum(4,1,AD_Value[3],5);
           
         
           




}}



	

