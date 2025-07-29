#include"stm32f10x.h"




void BKP_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    PWR_BackupAccessCmd(ENABLE); 

}