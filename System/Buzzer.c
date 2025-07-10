#include "stm32f10x.h"



/**
 * @brief 初始化蜂鸣器
 *  @param void
 * @return void
 */
void Buzzer_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_12); //初始化为高电平
}
/**
 * @brief 蜂鸣器开
 *  @param void
 * @return void
 */
void Buzzer_On(void)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}
/**
 * @brief 蜂鸣器关
 *  @param void
 * @return void
 */
void Buzzer_Off(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}
/**
 * @brief 蜂鸣器翻转
 *  @param void
 * @return void
 */
void Buzzer_Turn(void)//翻转
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12)));
}