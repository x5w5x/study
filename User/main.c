
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
uint16_t ad0,ad1,ad2,ad3;
float Voltage=0;
uint8_t keynum;
float angle=0;
int main(void)
{
	OLED_Init();
	AD_Init();







	while(1){
	ad0=AD_GetValue(ADC_Channel_0);
	ad1=AD_GetValue(ADC_Channel_1);
	ad2=AD_GetValue(ADC_Channel_2);
	ad3=AD_GetValue(ADC_Channel_3);
		
	OLED_ShowNum(1,1,ad0,5);
	OLED_ShowNum(2,1,ad1,5);
	OLED_ShowNum(3,1,ad2,5);
	OLED_ShowNum(4,1,ad3,5);
	Delay_ms(100);


	}
	
	

}
