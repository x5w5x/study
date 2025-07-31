#include"stm32f10x.h"
#include"FLASH.h"

#define Store_Data_Size 512
uint16_t Store_Data[Store_Data_Size];
#define Store_Data_Addr 0x0800FC00
void Store_Init(void)
{
    if(FLASH_ReadHalfWord(Store_Data_Addr) != 0xA5A5)
    {
        Flash_ErasePage(Store_Data_Addr);
        Flash_WriteHalfWord(Store_Data_Addr,0xA5A5);
        for(uint16_t i=1;i<512;i++)
        {
            Flash_WriteHalfWord(Store_Data_Addr+i*2,0x0000);
        }
    }
     for(uint16_t i=0;i<512;i++)
    {
        Store_Data[i] = FLASH_ReadHalfWord(Store_Data_Addr+i*2);
    }

}



void Store_Save(void)
{
    Flash_ErasePage(Store_Data_Addr);
    for(uint16_t i=0;i<512;i++)
    {
        Flash_WriteHalfWord(Store_Data_Addr+i*2,Store_Data[i]);
    }
}



void Store_Clear(void)
{
    for(uint16_t i=0;i<512;i++)
    {
        Store_Data[i] = 0x0000;
    }
    Store_Save();
}