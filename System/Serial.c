#include"stm32f10x.h"
#include"stdio.h"
#include"stdarg.h"
/*
1.开启时钟
2.配置引脚TX复用输出RX输入
3.配置USART
4.配置波特率

*/
uint8_t Serial_RxData;
uint8_t Serial_RxFlag = 0;
void Serial_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//开启USART1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启GPIOA时钟
    //配置引脚
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    //配置USART
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;//波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位数据位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//1位停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控制
    USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;//接收和发送
    USART_Init(USART1,&USART_InitStructure);
    //配置中断
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//使能接收中断
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置中断优先级分组
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);










    //使能USART1
    USART_Cmd(USART1,ENABLE);//使能USART1
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

void Serial_Printf(char *fmt,...)
{
    char str[100] = {0};
    va_list ap;
    va_start(ap,fmt);
    vsprintf(str,fmt,ap);
    va_end(ap);
    Serial_SendString(str);
}

uint8_t Serial_GetFlag(void)
{
    if(Serial_RxFlag == 1)
    {
        Serial_RxFlag = 0;
        return 1;
    }
    return 0;
}

uint8_t Serial_GetRxData(void)
{
    return Serial_RxData;
}





void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
    {
       Serial_RxData = USART_ReceiveData(USART1);
       Serial_RxFlag = 1;
        //处理接收到的数据
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
}