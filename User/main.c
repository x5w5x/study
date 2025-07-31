
#include "stm32f10x.h" 
#include "Delay.h"
// #include "led.h"
#include "Key.h"
// #include"Buzzer.h"
// #include"LightSensor.h"
#include "OLED.h"
// #include "CountSensor.h"
// #include "Encoder.h"
// #include"Timer.h"
// #include"pwm.h"
// #include"Serov.h"
// #include"IC.h"
// #include"AD.h"
// #include"DMA.h"
// #include"Serial.h"
// #include"W25Q64.h"
// #include"mpu6050.h"
#include"BKP.h"
#include"RTC.h"
uint8_t rxdata;

int main(void)
{
	

	OLED_Init();//初始化OLED
	Key_Init();//初始化按键
	OLED_ShowString(1,1,"WWDG TEST");
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST)==SET)
	{
		OLED_ShowString(2,1,"WWDGRST");
		Delay_ms(500);
		OLED_ShowString(2,1,"        ");
		Delay_ms(100);
	    RCC_ClearFlag();
	}
	else
	{
	    OLED_ShowString(3,1,"RST");
		Delay_ms(500);
		OLED_ShowString(3,1,"        ");
		Delay_ms(100);
	}
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);//使能WWDG时钟
	WWDG_SetPrescaler(WWDG_Prescaler_8);//设置WWDG分频系数
	WWDG_SetWindowValue(0x40 | 21);//设置WWDG窗口值
	WWDG_Enable(0x40 | 54);//使能WWDG


	while(1){
		Key_GetNum();
		
	
		OLED_ShowString(4,1,"FEED");
		Delay_ms(20);
		OLED_ShowString(4,1,"     ");
		Delay_ms(15);
		WWDG_SetCounter(0x40 | 54);//喂狗
}}



	

