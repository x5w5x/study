
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

uint16_t num=0;
uint8_t keynum;
float angle=0;
int main(void)
{
	OLED_Init();
	Key_Init();
	PWM_Init();
	IC_Init();
	OLED_ShowString(1,1,"Freq=");
PWM_SetPrescaler(720-1);//Freq=72M/(PSC+1)/100
PWM_SetCompare1(1);//Duty=CCR/100




	while(1){
	OLED_ShowNum(1,6,IC_GetFreq(),6);


	}
	
	

}

