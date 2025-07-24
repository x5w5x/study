
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


int main(void)
{
	OLED_Init();
	Serial_Init();
	

Serial_SendByte('a');
uint8_t data[]={0x42,0x43,0x44,0x45};
Serial_SendArray(data,4);
Serial_SendString("Hello World\r\n!");

Serial_SendNum(123456789);



	while(1){


	


	}
	
	

}
