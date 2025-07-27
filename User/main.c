
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
#include"IIC.h"
#include"mpu6050.h"
int16_t ax=0,ay,az,gx,gy,gz;
uint8_t data;
uint8_t id=0;
int main(void)
{
	
	
	OLED_Init();
	MPU6050_Init();

	// OLED_ShowHexNum(1,1,MPU6050_GetID(),3);


		
	while(1){
	
		
	
		


}}