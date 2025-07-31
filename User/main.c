
#include "stm32f10x.h" 
#include "Delay.h"
// #include "led.h"
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
// #include"W25Q64.h"
// #include"mpu6050.h"
// #include"BKP.h"
// #include"RTC.h"
// #include"FLASH.h"
#include"Store.h"
uint8_t keynum;
int main(void)
{
	
OLED_Init();
Key_Init();
Store_Init();



	while(1){
		
keynum=Key_GetNum();
if(keynum==1){
    Store_Data[1]+=1;
	Store_Data[2]+=3;
	Store_Save();
}
if(keynum==2){
  Store_Clear();
}


}}



	

