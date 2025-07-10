
#include "stm32f10x.h" 
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include"Buzzer.h"
#include"LightSensor.h"
#include "OLED.h"
// #include "OLED_Font.h"
int main(void)
{
	OLED_Init();
	OLED_ShowString(1,1,"Hello World!");
	OLED_ShowString(2,1,"^_^");
	OLED_ShowNum(3,1,123456789,9);
 


	

	while(1){
		    
	
		
		
		








	}
	
	

}