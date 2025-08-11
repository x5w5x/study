#include "stm32f10x.h"

uint16_t LED1_Count = 0;




typedef enum{
led_on,
led_off,
led_turn,
led_flash,
}Led_State;
/**
 * @name    LED_Init
 * @brief   LED��ʼ��
 * @param   ��
 * @retval  ��
 */
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2; //LED����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_1|GPIO_Pin_2);
}
/**
 * @name    LED_On
 * @brief   LED��
 * @param   ��
 * @retval  ��
 */
void LED_On(uint8_t LED)
{   
    if(LED == 1)
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);//���͵�ƽ
    }
    else if(LED == 2)
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_2);
    }
}
/**
 * @name    LED_Off
 * @brief   LED��
 * @param   ��
 * @retval  ��
 */
void LED_Off(uint8_t LED)
{
    if(LED == 1)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_1);//���ߵ�ƽ
    }
    else if(LED == 2)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_2);
    }
}

/**
 *  @name    LED_Turn
 * @brief   LED��ת
 * @param   ��
 * @retval  ��
 *  
 */
void LED_Turn(uint8_t LED)//��ת
{
    if(LED == 1)
    {
        GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1)));//��ת��ƽ
    }
    else if(LED == 2)
    {
        GPIO_WriteBit(GPIOA, GPIO_Pin_2, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2)));
    }
}

uint8_t LED_Tick_Flag=0;
void LED_Tick(void)
{ if(LED_Tick_Flag){
    LED1_Count++;
    LED1_Count%= 1000;
    if(LED1_Count<500)
    {
        LED_On(1);
    }
    else
    {
        LED_Off(1);
    }
}
}


void LED_Set(Led_State led_state)
{
    if(led_state == led_on)
    {
        LED_Tick_Flag=0;
        LED_On(1);
    }
    else if(led_state == led_off)
    {
        LED_Tick_Flag=0;
        LED_Off(1);
    }
    else if(led_state == led_turn)
    {
        LED_Tick_Flag=0;
        LED_Turn(1);
    }
    else if(led_state == led_flash)
    {
        LED_Tick_Flag=1;
    }

}