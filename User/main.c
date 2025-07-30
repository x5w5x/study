
#include "stm32f10x.h" 
#include "Delay.h"
// #include "led.h"
// #include "Key.h"
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
#include"BKP.h"
#include"RTC.h"
uint8_t rxdata;

int main(void)
{
	

	OLED_Init();
	

OLED_ShowString(1,1,"CNT:");
OLED_ShowString(2,1,"ALR:");
OLED_ShowString(3,1,"ALRF:");



	


		
	while(1){
		


}}