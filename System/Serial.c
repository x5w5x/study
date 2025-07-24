#include"stm32f10x.h"
#include"stdio.h"

/*
1.����ʱ��
2.��������TX�������RX����
3.����USART
4.���ò�����

*/

void Serial_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//����USART1ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//����GPIOAʱ��
    //��������
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    // GPIO_Init(GPIOA,&GPIO_InitStructure);
    //����USART
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;//������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ����λ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//1λֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//��У��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
    USART_InitStructure.USART_Mode = USART_Mode_Tx;//���պͷ���
    USART_Init(USART1,&USART_InitStructure);
    USART_Cmd(USART1,ENABLE);//ʹ��USART1
}

void Serial_SendByte(uint8_t byte)
{
    USART_SendData(USART1,byte);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}


void Serial_SendArray(uint8_t *array,uint16_t len)
{
    for(uint16_t i = 0;i < len;i++)
    {
        Serial_SendByte(array[i]);
    }
}


void Serial_SendString(char *str)
{
    while(*str)
    {
        Serial_SendByte(*str++);
    }
}

void Serial_SendNum(uint32_t num)
{
    char str[10] = {0};
    sprintf(str,"%d",num);
    Serial_SendString(str);
}