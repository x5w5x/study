#include "stm32f10x.h"

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_1|GPIO_Pin_2);
}

void LED_On(uint8_t LED)
{   
    if(LED == 1)
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
    }
    else if(LED == 2)
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_2);
    }
}

void LED_Off(uint8_t LED)
{
    if(LED == 1)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_1);
    }
    else if(LED == 2)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_2);
    }
}


void LED_Turn(uint8_t LED)//·­×ª
{
    if(LED == 1)
    {
        GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1)));
    }
    else if(LED == 2)
    {
        GPIO_WriteBit(GPIOA, GPIO_Pin_2, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2)));
    }
}