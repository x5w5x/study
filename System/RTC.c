#include"stm32f10x.h"
#include<time.h>
#include"BKP.h"
uint16_t RTC_Time[]={2025,7,29,22,29,0};


void RTC_SetTime(uint16_t *time)
{
    time_t time_cnt;
    struct tm time_data;
    time_data.tm_year=time[0]-1900;
    time_data.tm_mon=time[1]-1;
    time_data.tm_mday=time[2];
    time_data.tm_hour=time[3];
    time_data.tm_min=time[4];
    time_data.tm_sec=time[5];
    time_cnt=mktime(&time_data)-8*60*60;//转换为秒时序偏移8小时
    RTC_SetCounter(time_cnt);
    RTC_WaitForLastTask();//等待RTC寄存器写入完成
    
}
/*
1.开启BKP&PWR时钟
2.启动RTC时钟
3.配置RTC时钟源
4.配置等待函数
5.配置预分频器
6.配置闹钟（中断）


*/
//普通模式
// void RTC_Init(void)
// {   //开启BKP&PWR时钟
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
//     PWR_BackupAccessCmd(ENABLE);
//     //启动RTC时钟
//     RCC_LSEConfig(RCC_LSE_ON);//开启外部晶振
//     while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET);//等待外部晶振启动
//     //配置RTC时钟源
//     RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
//     RCC_RTCCLKCmd(ENABLE);//启动RTC时钟
//     //配置等待函数
//     RTC_WaitForSynchro();//等待RTC寄存器同步
//     RTC_WaitForLastTask();//等待RTC寄存器写入完成
//     //配置预分频器
//     RTC_SetPrescaler(32768-1);//设置预分频器
//    RTC_WaitForLastTask();//等待RTC寄存器写入完成


//    RTC_SetTime(RTC_Time);
// }
//LSE不稳定，使用LSI
void RTC_Init(void)
{
    BKP_Init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);
	
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		RCC_LSICmd(ENABLE);
		while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) != SET);
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
		RCC_RTCCLKCmd(ENABLE);
		
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		
		RTC_SetPrescaler(40000 - 1);
		RTC_WaitForLastTask();
		
		RTC_SetTime(RTC_Time);
		
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
	}
	else
	{
		RCC_LSICmd(ENABLE);				//即使不是第一次配置，也需要再次开启LSI时钟
		while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) != SET);
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
		RCC_RTCCLKCmd(ENABLE);
		
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
}


void RTC_ReadTime(uint16_t *time)
{
     time_t time_cnt;
    struct tm time_data;
    time_cnt=RTC_GetCounter()+8*60*60;
    time_data=*localtime(&time_cnt);
    time[0]=time_data.tm_year+1900;
    time[1]=time_data.tm_mon+1;
    time[2]=time_data.tm_mday;
    time[3]=time_data.tm_hour;
    time[4]=time_data.tm_min;
    time[5]=time_data.tm_sec;

}

// //BKP模式

// void RTC_Init(void)
// {   //开启BKP&PWR时钟
//     BKP_Init();
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
//     PWR_BackupAccessCmd(ENABLE);
//     //启动RTC时钟
//     if(BKP_ReadBackupRegister(BKP_DR1)!=0x5A5A)
//     {
        
//         RCC_LSEConfig(RCC_LSE_ON);//开启外部晶振
//         while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET);//等待外部晶振启动
//         //配置RTC时钟源
//         RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
//         RCC_RTCCLKCmd(ENABLE);//启动RTC时钟
//         //配置等待函数
//         RTC_WaitForSynchro();//等待RTC寄存器同步
//         RTC_WaitForLastTask();//等待RTC寄存器写入完成
//         //配置预分频器
//         RTC_SetPrescaler(32768-1);//设置预分频器
//         RTC_WaitForLastTask();//等待RTC寄存器写入完成


//         RTC_SetTime(RTC_Time);
//         BKP_WriteBackupRegister(BKP_DR1,0x5A5A);
//     }
//     else
//     {
//         RTC_WaitForSynchro();//等待RTC寄存器同步
//         RTC_WaitForLastTask();//等待RTC寄存器写入完成
//     }







    
// }

