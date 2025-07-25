
#include "stm32f10x.h" 
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include"Buzzer.h"
#include"LightSensor.h"
#include "OLED.h"
#include "CountSensor.h"
#include "Encoder.h"
#include"Timer.h"
#include"pwm.h"
#include"Serov.h"
#include"IC.h"
#include"AD.h"
#include"DMA.h"
#include"Serial.h"
uint8_t data;
uint8_t keynum=0;
int main(void)
{Key_Init();
	OLED_Init();
	Serial_Init();
	

	





	while(1){

if(Serial_GetFlag()==1){
OLED_ShowString(4,1,Serial_RXString);


	

}
}}