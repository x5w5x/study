
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

int main(void)
{
	OLED_Init();
	Serial_Init();
	





	while(1){

// if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
// 	{
// 	    data=USART_ReceiveData(USART1);
// 		OLED_ShowHexNum(1,1,data,2);
// 	}
if(Serial_GetFlag()==1)
	{
		data=Serial_GetRxData();
		Serial_Printf("data=%s","hello");
		OLED_ShowHexNum(1,1,data,2);
	}
	


	}
	
	

}
