#include "stm32f10x.h"
#include"Delay.h"
#include "Key.h"

#define KEY_PRESSED 1
#define KEY_RELEASED 0

#define KEY_TIME_DOUBLE 200
#define KEY_TIME_LONG 1000
#define KEY_TIME_REPEAT 100

uint8_t Key_Flag;
uint8_t Key_Num;
/**
 * @Key_Init
 * @brief   ��ʼ������
 * @param   ��
 * @retval  ��
 */
void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_11;//��������Ĭ��Ϊ�ߵ�ƽ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 *  @Key_GetNum
 * @brief   ��ȡ����ֵ
 * @param   ��
 * @retval  ����ֵ
 * @note    ����ʽ
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


// uint8_t Key_GetState(void)
// {
//     uint8_t key = 0;
//     if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0){
//         key = 1;
//     }
//     if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)==0){
//         key = 2;
//     }

//     return key;
// }



// //��ʱ���ж�ɨ�谴��
// void Key_Tick(void)
// {
//     static uint8_t Count;
//     static uint8_t CurrState, LastState;
//     Count++;
//     if(Count>=10){
//         Count = 0;
//         LastState = CurrState;
//        CurrState= Key_GetState();
//        if(CurrState==0&&LastState!=0){
//            //��������
//            Key_Num =LastState;
//        }
//     }
// }
// /**
//  * @brief    ��ȡ����ֵ
//  * @retval  ��
//  * @note    ������ʽ
//  * @return uint8_t 
//  */
// uint8_t Key_GetNum(void)
// {
//     uint8_t Temp;
//     Temp= Key_Num;
//     Key_Num = 0;
//     return Temp;
// }



uint8_t Key_GetState(void)
{
    
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0){
        return KEY_PRESSED;
    }
    

    return KEY_RELEASED;
}



void Key_Tick(void)
{
    static uint8_t Count;
    static uint8_t CurrState, LastState;
    static uint8_t s;
    static uint16_t Time;
    if(Time>0)
    Time--;
    Count++;
    if(Count>=10){
        Count = 0;
        LastState = CurrState;
       CurrState= Key_GetState();
       if(CurrState==KEY_PRESSED)
       {
           Key_Flag |= KEY_HOLD;
       }
       else 
       {
        Key_Flag &= ~KEY_HOLD;
       }
       if(CurrState==KEY_PRESSED&&LastState==KEY_RELEASED)
      {
        Key_Flag|= KEY_DOWN;
      }
       if(CurrState==KEY_RELEASED&&LastState==KEY_PRESSED)
       {
           Key_Flag |= KEY_UP;
       }
       if(s==0)
       {
           if(CurrState==KEY_PRESSED)
           {
           Time=KEY_TIME_LONG;
           s=1;}
       }
       else if(s==1)
       {
           if(CurrState==KEY_RELEASED)
           {
            Time=KEY_TIME_DOUBLE;
           s=2;
           }
           else if (Time==0)
           {
            Time=KEY_TIME_REPEAT;
            Key_Flag |= KEY_LONG;
            s=4;
           }
       }
       else if(s==2)
       {
            if(CurrState==KEY_PRESSED)
            {
                Key_Flag |= KEY_DOUBLE;
                s=3;
            }
            else if(Time==0)
            {
                Key_Flag |= KEY_SINGLE;
                s=0;
            }
           
       }
       else if(s==3)
       {
           if(CurrState==KEY_RELEASED)
           {
            s=0;
            }
       }
       else if(s==4)
       {
           if(CurrState==KEY_RELEASED)
           {
            s=0;
           }
           else if(Time==0)
           {
            Time=KEY_TIME_REPEAT;
            Key_Flag |= KEY_REPEAT;
            s=4;
           }
       }







    }
}




uint8_t Key_Check(uint8_t Flag)
{
    if(Key_Flag & Flag)
    {
        if(Flag !=KEY_HOLD)
        Key_Flag &= ~Flag;
        return 1;
    }
    return 0;
}