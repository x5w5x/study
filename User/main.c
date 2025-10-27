/*
 * @Author: xwx
 * @Date: 2025-09-20 16:59:21
 * @LastEditTime: 2025-10-27 20:02:11
 * @FilePath: \learn\User\main.c
 */

#include "stm32f10x.h"
#include "Delay.h"
#include "rc522.h"
#include "serial.h"

uint8_t status;
extern uint8_t CT[];
extern uint8_t SN[];
extern uint8_t RFID[];
uint8_t card_1[4]  = {0x4A, 0xD6, 0x67, 0x1A};
uint8_t card_1_bit = 0;
extern uint8_t key[6];
int main()
{

    Serial_Init();
    Serial_Printf("RFID Start ......\n");
    RC522_Init(); //
    Delay_ms(300);

    while (1) {
        // RC522_Handel();
        status = PcdRequest(PICC_REQALL, CT); // 寻卡
        if (status == MI_OK) {
            status = MI_ERR;
            status = PcdAnticoll(SN); // 防冲撞
            if (status == MI_OK) {

                status = MI_ERR;
                Serial_Printf("======================\n");
                ShowID(SN);
                if (SN[0] == card_1[0] && SN[1] == card_1[1] && SN[2] == card_1[2] && SN[3] == card_1[3]) {
                    Serial_Printf("User>>>CARD_1\r\n");
                    card_1_bit = 1;
                }
                status = PcdSelect(SN);
                if (status == MI_OK) {
                    status = MI_ERR;
                    Serial_Printf("select card ok!!!\r\n");
                    status = PcdAuthState(PICC_AUTHENT1A, 0x07, key, SN);
                    if (status == MI_OK) {
                        Serial_Printf("Auth ok!!!\r\n");
                        status = MI_ERR;
                        status = PcdRead(4,RFID);
                        if (status == MI_OK) {
                            Serial_Printf("Read ok!!!\r\n");
                            Serial_Printf("余额>>>%X0元\r\n",RFID[0]);
                            Serial_Printf("RFID>>>0:%02X 1:%02X 2:%02X 3:%02X\r\n", RFID[0], RFID[1], RFID[2], RFID[3]);
                            RFID[0]++;
                            status = MI_ERR;
                            status = PcdWrite(4,RFID);
                            if (status == MI_OK) {
                                Serial_Printf("Write ok!!!\r\n");
                            }
                        }
                    }
                }
            }

            Serial_Printf("======================\n");
            WaitCardOff();
        } else {
            Serial_Printf("NO Card\n");
        }

        Delay_ms(300);
        // Serial_Printf("#");
    }
}