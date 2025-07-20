
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

	 Encoder_Init();






	while(1){
		num=Encoder_Get();
OLED_ShowNum(1,1,num,5);
	}
	
	

}

