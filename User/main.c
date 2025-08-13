
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
#include"pwm.h"
// #include"Serov.h"
#include"IC.h"
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
int16_t num;
#include"Max7219.h"

int main(void)
{	
      OLED_Init();
      LED_Init();
      // Timer_Init();
      Key_Init();
      // LED_Set(led_flash);
      PWM_Init();
      IC_Init();
      PWM_SetCompare1(50);
      PWM_SetPrescaler(720-1);

     



      
     


	while(1){
   
      OLED_ShowNum(1,1,IC_GetDuty(),5);
      OLED_ShowNum(2,1,IC_GetFreq(),5);
           
         
           




}}



	

