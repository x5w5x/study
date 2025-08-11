#include "stm32f10x.h"
#include"Delay.h"

uint8_t Key_Num;
/**
 * @Key_Init
 * @brief   初始化按键
 * @param   无
 * @retval  无
 */
void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_11;//按键引脚默认为高电平
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 *  @Key_GetNum
 * @brief   获取按键值
 * @param   无
 * @retval  按键值
 * @note    阻塞式
 *  
 */
// uint8_t Key_GetNum(void)
// {
//     uint8_t key = 0;
//     if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0){
//         Delay_ms(20);
//         while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0);
//         Delay_ms(20);
//         key = 1;
//     }
//     if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)==0){
//         Delay_ms(20);
//         while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)==0);
//         Delay_ms(20);
//         key = 2;
//     }
//     return key;
// }


uint8_t Key_GetState(void)
{
    uint8_t key = 0;
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0){
        key = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)==0){
        key = 2;
    }

    return key;
}



//定时器中断扫描按键
void Key_Tick(void)
{
    static uint8_t Count;
    static uint8_t CurrState, LastState;
    Count++;
    if(Count>=10){
        Count = 0;
        LastState = CurrState;
       CurrState= Key_GetState();
       if(CurrState==0&&LastState!=0){
           //按键按下
           Key_Num =LastState;
       }
    }
}
/**
 * @brief    获取按键值
 * @retval  无
 * @note    非阻塞式
 * @return uint8_t 
 */
uint8_t Key_GetNum(void)
{
    uint8_t Temp;
    Temp= Key_Num;
    Key_Num = 0;
    return Temp;
}