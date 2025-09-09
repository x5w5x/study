
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
#include"HCSR04.h"




int main(void)
{	

      float distance;
      OLED_Init();

      OLED_Clear();
      HCSR04_Init();
      OLED_ShowString(1,1,"HCSR04:");
      // OLED_ShowNum(2,1,(uint32_t)HCSR04_Read(),8);
 
      // AD_Init();



 while(1) {
// OLED_ShowNum(1,1,AD_Value[0],4);
//       Delay_ms(100);
distance=HCSR04_GetDistance();

      OLED_ShowNum(2,1,distance,8);
      Delay_ms(60);
      // OLED_ShowSignedNum(2,1,distance,8);
    }

}



	
