
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

int16_t num=0;
uint8_t keynum;
float angle=0;
int main(void)
{
	OLED_Init();
Timer_Init();
	 Encoder_Init();






	while(1){
	
OLED_ShowSignedNum(1,1,num,5);

	}
	
	

}


void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		num=Encoder_Get();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}