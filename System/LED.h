#ifndef _LED_H_
#define _LED_H_
typedef enum{
led_on,
led_off,
led_turn,
led_flash,
}Led_State;

void LED_Init(void);
void LED_On(uint8_t LED);
void LED_Off(uint8_t LED);
void LED_Turn(uint8_t LED);
void LED_Tick(void);
void LED_Set(Led_State led_state);
#endif
