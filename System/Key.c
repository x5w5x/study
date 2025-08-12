#include "stm32f10x.h"
#include"Delay.h"
#include "Key.h"

#define KEY_PRESSED 1 //定义按下
#define KEY_RELEASED 0 //定义释放

#define KEY_TIME_DOUBLE 200 //双击时间阈值
#define KEY_TIME_LONG 1000 //长按时间阈值
#define KEY_TIME_REPEAT 100 //重复按键时间阈值


uint8_t Key_Flag[4]; //按键标志位
uint8_t Key_Num; //按键值
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
    //1，2按键GPIO初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_11;//按键引脚默认为高电平
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //3，4按键GPIO初始化
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;//按键引脚默认为高电平
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//上拉输入
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



// //定时器中断扫描按键
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
//            //按键按下
//            Key_Num =LastState;
//        }
//     }
// }
// /**
//  * @brief    获取按键值
//  * @retval  无
//  * @note    非阻塞式
//  * @return uint8_t 
//  */
// uint8_t Key_GetNum(void)
// {
//     uint8_t Temp;
//     Temp= Key_Num;
//     Key_Num = 0;
//     return Temp;
// }



// uint8_t Key_GetState()
// {
//     if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0){
//         return KEY_PRESSED;
//     }
//     return KEY_RELEASED;
// }



// void Key_Tick(void)
// {
//     static uint8_t Count;
//     static uint8_t CurrState, LastState;
//     static uint8_t s;
//     static uint16_t Time;
//     if(Time>0)
//     Time--;
//     Count++;
//     if(Count>=10){
//         Count = 0;
//         LastState = CurrState;
//        CurrState= Key_GetState();
//        if(CurrState==KEY_PRESSED)
//        {
//            Key_Flag |= KEY_HOLD;
//        }
//        else 
//        {
//         Key_Flag &= ~KEY_HOLD;
//        }
//        if(CurrState==KEY_PRESSED&&LastState==KEY_RELEASED)
//       {
//         Key_Flag|= KEY_DOWN;
//       }
//        if(CurrState==KEY_RELEASED&&LastState==KEY_PRESSED)
//        {
//            Key_Flag |= KEY_UP;
//        }
//        if(s==0)
//        {
//            if(CurrState==KEY_PRESSED)
//            {
//            Time=KEY_TIME_LONG;
//            s=1;}
//        }
//        else if(s==1)
//        {
//            if(CurrState==KEY_RELEASED)
//            {
//             Time=KEY_TIME_DOUBLE;
//            s=2;
//            }
//            else if (Time==0)
//            {
//             Time=KEY_TIME_REPEAT;
//             Key_Flag |= KEY_LONG;
//             s=4;
//            }
//        }
//        else if(s==2)
//        {
//             if(CurrState==KEY_PRESSED)
//             {
//                 Key_Flag |= KEY_DOUBLE;
//                 s=3;
//             }
//             else if(Time==0)
//             {
//                 Key_Flag |= KEY_SINGLE;
//                 s=0;
//             }
           
//        }
//        else if(s==3)
//        {
//            if(CurrState==KEY_RELEASED)
//            {
//             s=0;
//             }
//        }
//        else if(s==4)
//        {
//            if(CurrState==KEY_RELEASED)
//            {
//             s=0;
//            }
//            else if(Time==0)
//            {
//             Time=KEY_TIME_REPEAT;
//             Key_Flag |= KEY_REPEAT;
//             s=4;
//            }
//        }







//     }
// }




// uint8_t Key_Check(uint8_t Flag)
// {
    

//     if(Key_Flag & Flag)
//     {
//         if(Flag !=KEY_HOLD)
//         Key_Flag &= ~Flag;
//         return 1;
//     }
//     return 0;
// }








//获取按键状态

uint8_t Key_GetState(uint8_t key_n)
{
   if(key_n==KEY_1){
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0){
        return KEY_PRESSED;
    }
    }
    else if (key_n==KEY_2)
    {
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)==0){
        return KEY_PRESSED;
    }
    }
    else if (key_n==KEY_3)
    {
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)==1){
        return KEY_PRESSED;
    }
    }
    else if (key_n==KEY_4)
    {
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)==1)
        return KEY_PRESSED;
    }
 


    return KEY_RELEASED;
}


//定时器中断扫描按键

void Key_Tick(void)
{
    static uint8_t Count,i;
    static uint8_t CurrState[4], LastState[4];
    static uint8_t s[4];
    static uint16_t Time[4];
    for(i=0;i<4;i++){
    if(Time[i]>0)
    {
    Time[i]--; 
    }
    }
   
    Count++;
    if(Count>=10){
        Count = 0;
        for(i=0;i<4;i++){
        LastState[i] = CurrState[i];
       CurrState[i]= Key_GetState(i);
       if(CurrState[i]==KEY_PRESSED)
       {
           Key_Flag[i] |= KEY_HOLD;
       }
       else 
       {
        Key_Flag[i] &= ~KEY_HOLD;
       }
       if(CurrState[i]==KEY_PRESSED&&LastState[i]==KEY_RELEASED)
      {
        Key_Flag[i]|= KEY_DOWN;
      }
       if(CurrState[i]==KEY_RELEASED&&LastState[i]==KEY_PRESSED)
       {
           Key_Flag[i] |= KEY_UP;
       }
       if(s[i]==0)
       {
           if(CurrState[i]==KEY_PRESSED)
           {
            Time[i]=KEY_TIME_LONG;
            s[i]=1;
            }
       }
       else if(s[i]==1)
       {
           if(CurrState[i]==KEY_RELEASED)
           {
            Time[i]=KEY_TIME_DOUBLE;
            s[i]=2;
           }
           else if (Time[i]==0)
           {
                Time[i]=KEY_TIME_REPEAT;
                Key_Flag[i] |= KEY_LONG;
                s[i]=4;
           }
       }
       else if(s[i]==2)
       {
            if(CurrState[i]==KEY_PRESSED)
            {
                Key_Flag[i] |= KEY_DOUBLE;
                s[i]=3;
            }
            else if(Time[i]==0)
            {
                Key_Flag[i] |= KEY_SINGLE;
                s[i]=0;
            }
           
       }
       else if(s[i]==3)
       {
           if(CurrState[i]==KEY_RELEASED)
           {
                s[i]=0;
            }
       }
       else if(s[i]==4)
       {
           if(CurrState[i]==KEY_RELEASED)
           {
            s[i]=0;
           }
           else if(Time[i]==0)
           {
            Time[i]=KEY_TIME_REPEAT;
            Key_Flag[i] |= KEY_REPEAT;
            s[i]=4;
           }
       }
    }
    }
}


/**
 * @brief  检查按键状态
 * 
 * @param n按键编号
 * @param Flag按键状态
 * @return uint8_t 
 */
uint8_t Key_Check(uint8_t n, uint8_t Flag)
{
    if(Key_Flag[n] & Flag)
    {
        if(Flag !=KEY_HOLD)
        Key_Flag[n] &= ~Flag;
        return 1;
    }
    return 0;
}
