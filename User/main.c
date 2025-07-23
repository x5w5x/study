
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



int main(void)
{
	OLED_Init();
	
	AD_Init();








	while(1){
	
	OLED_ShowNum(1,1,AD_Value[0],4);
	OLED_ShowNum(2,1,AD_Value[1],4);
	OLED_ShowNum(3,1,AD_Value[2],4);
	OLED_ShowNum(4,1,AD_Value[3],4);

	


	}
	
	

}
