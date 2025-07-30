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
    time_cnt=mktime(&time_data)-8*60*60;//ת��Ϊ��ʱ��ƫ��8Сʱ
    RTC_SetCounter(time_cnt);
    RTC_WaitForLastTask();//�ȴ�RTC�Ĵ���д�����
    
}
/*
1.����BKP&PWRʱ��
2.����RTCʱ��
3.����RTCʱ��Դ
4.���õȴ�����
5.����Ԥ��Ƶ��
6.�������ӣ��жϣ�


*/
//��ͨģʽ
// void RTC_Init(void)
// {   //����BKP&PWRʱ��
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
//     PWR_BackupAccessCmd(ENABLE);
//     //����RTCʱ��
//     RCC_LSEConfig(RCC_LSE_ON);//�����ⲿ����
//     while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET);//�ȴ��ⲿ��������
//     //����RTCʱ��Դ
//     RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
//     RCC_RTCCLKCmd(ENABLE);//����RTCʱ��
//     //���õȴ�����
//     RTC_WaitForSynchro();//�ȴ�RTC�Ĵ���ͬ��
//     RTC_WaitForLastTask();//�ȴ�RTC�Ĵ���д�����
//     //����Ԥ��Ƶ��
//     RTC_SetPrescaler(32768-1);//����Ԥ��Ƶ��
//    RTC_WaitForLastTask();//�ȴ�RTC�Ĵ���д�����


//    RTC_SetTime(RTC_Time);
// }
//LSE���ȶ���ʹ��LSI
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
		RCC_LSICmd(ENABLE);				//��ʹ���ǵ�һ�����ã�Ҳ��Ҫ�ٴο���LSIʱ��
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

// //BKPģʽ

// void RTC_Init(void)
// {   //����BKP&PWRʱ��
//     BKP_Init();
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
//     PWR_BackupAccessCmd(ENABLE);
//     //����RTCʱ��
//     if(BKP_ReadBackupRegister(BKP_DR1)!=0x5A5A)
//     {
        
//         RCC_LSEConfig(RCC_LSE_ON);//�����ⲿ����
//         while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET);//�ȴ��ⲿ��������
//         //����RTCʱ��Դ
//         RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
//         RCC_RTCCLKCmd(ENABLE);//����RTCʱ��
//         //���õȴ�����
//         RTC_WaitForSynchro();//�ȴ�RTC�Ĵ���ͬ��
//         RTC_WaitForLastTask();//�ȴ�RTC�Ĵ���д�����
//         //����Ԥ��Ƶ��
//         RTC_SetPrescaler(32768-1);//����Ԥ��Ƶ��
//         RTC_WaitForLastTask();//�ȴ�RTC�Ĵ���д�����


//         RTC_SetTime(RTC_Time);
//         BKP_WriteBackupRegister(BKP_DR1,0x5A5A);
//     }
//     else
//     {
//         RTC_WaitForSynchro();//�ȴ�RTC�Ĵ���ͬ��
//         RTC_WaitForLastTask();//�ȴ�RTC�Ĵ���д�����
//     }







    
// }

