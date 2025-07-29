#ifndef _RTC_H
#define _RTC_H

void RTC_Init(void);
void RTC_SetTime(uint16_t *time);
void RTC_ReadTime(uint16_t *time);
extern uint16_t RTC_Time[];
#endif // !_RTC_H