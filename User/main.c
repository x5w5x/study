
#include "stm32f10x.h" 
#include "Delay.h"
#include "led.h"
#include "Key.h"
#include"Buzzer.h"





int main(void)
{
	
	LED_Init();
	Key_Init();
	Buzzer_Init();
	
	Buzzer_Turn();
	Delay_ms(1000);
	Buzzer_Turn();
	
	
	while(1){

		







	}
	
	
}
