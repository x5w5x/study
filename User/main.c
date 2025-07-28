
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
#include"W25Q64.h"
#include"mpu6050.h"
uint8_t MID;
uint16_t DID;
uint8_t wdata[]={0x11,0x22,0x33,0x44};
uint8_t rdata[4];
int main(void)
{
	
	
	OLED_Init();
	W25Q64_Init();


W25Q64_ReadID(&MID,&DID);
	OLED_ShowHexNum(1,1,MID,3);
	OLED_ShowHexNum(1,5,DID,4);


		
	while(1){
	
		
	
		


}}