
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
uint8_t wdata[]={0x55,0x66,0x77,0x88};
uint8_t rdata[4];
int main(void)
{
	
	
	OLED_Init();
	W25Q64_Init();

	W25Q64_SectorErase(0x000000);
	W25Q64_PageProgram(0x000000,wdata,4);
	W25Q64_ReadData(0x000000,rdata,4);
	
	OLED_ShowHexNum(2,3,wdata[0],2);
	OLED_ShowHexNum(2,6,wdata[1],2);
	OLED_ShowHexNum(2,9,wdata[2],2);
	OLED_ShowHexNum(2,12,wdata[3],2);

	OLED_ShowHexNum(4,3,rdata[0],2);
	OLED_ShowHexNum(4,6,rdata[1],2);
	OLED_ShowHexNum(4,9,rdata[2],2);
	OLED_ShowHexNum(4,12,rdata[3],2);

	// OLED_ShowHexNum(1,1,MPU6050_GetID(),3);


		
	while(1){
	
		
	
		


}}