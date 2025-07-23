#include"stm32f10x.h"

uint16_t DMA_Size=0;


void DMA_INIT(uint32_t AddrA, uint32_t AddrB, uint16_t Size)
{
    DMA_Size=Size;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//ʹ��DMA1ʱ��

    DMA_InitTypeDef DMA_InitStructure;//DMA��ʼ���ṹ��
    DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;//�����ַ��32λ��
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݿ��
    DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;//�ڴ��ַ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�ڴ����ݿ��
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//���䷽��
    DMA_InitStructure.DMA_BufferSize = Size;//����������
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//�����ַ����
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�ڴ��ַ����
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //����ģʽ Ϊ����ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//���ȼ�
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;//���赽����ģʽ
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);//��ʼ��DMA1ͨ��5

    DMA_Cmd(DMA1_Channel1,DISABLE);//ʹ��DMA1ͨ��5
}

void DMA_Transfer(void)
{
    DMA_Cmd(DMA1_Channel1,DISABLE);//�ر�DMA1ͨ��5
    DMA_SetCurrDataCounter(DMA1_Channel1,DMA_Size);//����DMA1ͨ��5����������
    DMA_Cmd(DMA1_Channel1,ENABLE);//ʹ��DMA1ͨ��5

    while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);//�ȴ��������
    DMA_ClearFlag(DMA1_FLAG_TC1);//���������ɱ�־
}