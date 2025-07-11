
#include "stm32f10x.h" 
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include"Buzzer.h"
#include"LightSensor.h"
#include "OLED.h"
#include "CountSensor.h"
#include "Encoder.h"
int main(void)
{
int16_t num=0;
	
	OLED_Init();
	Encoder_Init();
	// OLED_ShowString(1,1,"Hello World!");
	// OLED_ShowString(2,1,"^_^");
	
 


	

	while(1){
		num=Encoder_Get();
	
		Delay_ms(100);
		
		OLED_ShowNum(3,1,num,6);








	}
	
	

}