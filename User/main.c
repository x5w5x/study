/*
 * @Author: xwx
 * @Date: 2025-09-20 16:59:21
 * @LastEditTime: 2025-10-24 21:44:48
 * @FilePath: \learn\User\main.c
 */


#include "stm32f10x.h"
#include "Delay.h"
#include"rc522.h"
#include "serial.h"
int main(){

    Serial_Init();
 Serial_Printf("RFID Start ......\n");
    // RC522_Init();         //
    Delay_ms(300);


    while (1)
    {
        // RC522_Handel();
        Delay_ms(300);
        Serial_Printf("#");
    }
}