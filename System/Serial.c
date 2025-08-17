#include"stm32f10x.h"
#include"stdio.h"
#include"stdarg.h"
#include"Serial.h"
/*
1.����ʱ��
2.��������TX�������RX����
3.����USART
4.���ò�����

*/
uint8_t Serial_RxData;
uint8_t Serial_RxFlag = 0;
uint8_t Serial_TXPacket[256];
uint8_t Serial_RXPacket[256];
char Serial_RXString[256];
/**
 * @brief    ���ڳ�ʼ��
 * @param    ��
 * @retval   ��
 * 
 */
void Serial_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//����USART1ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//����GPIOAʱ��
    //��������
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    //����USART
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;//������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ����λ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//1λֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//��У��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
    USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;//���պͷ���
    USART_Init(USART1,&USART_InitStructure);
    //�����ж�
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//ʹ�ܽ����ж�
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����
    //����NVIC
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����USART1�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж�
    NVIC_Init(&NVIC_InitStructure);//��ʼ��

    //ʹ��USART1
    USART_Cmd(USART1,ENABLE);//ʹ��USART1
}
/**
 * @brief  ����һ���ֽ�
 * 
 * @param byte  Ҫ���͵��ֽ�
 */
void Serial_SendByte(uint8_t byte)
{
    USART_SendData(USART1,byte);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

/**
 * @brief ��������
 * 
 * @param array   ����
 * @param len    ���鳤��
 */
void Serial_SendArray(uint8_t *array,uint16_t len)
{
    for(uint16_t i = 0;i < len;i++)
    {
        Serial_SendByte(array[i]);
    }
}

/**
 * @brief �����ַ���
 * 
 * @param str  �ַ���
 */
void Serial_SendString(char *str)
{
    while(*str)
    {
        Serial_SendByte(*str++);
    }
}
/**
 * @brief ��������
 * 
 * @param num  ����
 */
void Serial_SendNum(uint32_t num)
{
    char str[10] = {0};
    sprintf(str,"%d",num);
    Serial_SendString(str);
}
/**
 * @brief ��ʽ�����
 * 
 * @param fmt 
 * @param ... 
 */
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
/**
 * @brief   ��ȡ��������
 * 
 * @return uint8_t 
 */
uint8_t Serial_GetRxData(void)
{
    return Serial_RxData;
}

/**
 * @brief �������ݰ�   
 * 
 * @param len 
 */
void Serial_SendPacket(uint16_t len)
{
    Serial_SendByte(0xFF);
    Serial_SendArray(Serial_TXPacket,len);
    Serial_SendByte(0xFE);
}

#if SERIAL_RX_MODE == 1
void USART1_IRQHandler(void)
{
    static uint8_t RxSate = 0;
     static uint8_t pRxSate = 0;
    if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
    {
        uint8_t RxData = USART_ReceiveData(USART1);
     if(RxSate == 0)
        {
            if(RxData == 0xFF)
            {
                RxSate = 1;
                pRxSate=0;
            }
        }
        else if(RxSate == 1)
        {
            Serial_RXPacket[pRxSate++] = RxData;
            if(pRxSate == 4){
                RxSate = 2;
            }
        }
        else if(RxSate == 2)
        {
            if(RxData == 0xFE)
            {
                RxSate = 0;
                Serial_RxFlag= 1;

            }
          
        }
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
}

#elif SERIAL_RX_MODE == 2

void USART1_IRQHandler(void)
{
    static uint8_t RxState = 0;//����״̬
    static uint8_t pRxSate = 0;//�������ݰ�λ��
    if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
    {
        uint8_t RxData = USART_ReceiveData(USART1);
     if(RxState == 0)
        {
            if(RxData == '@')
            {
                RxState = 1;
                pRxSate=0;
            }
        }
        else if(RxState == 1)
        {   if(RxData=='\r')
            {
                RxState = 2;
                
            }
            else
            {
           Serial_RXString[pRxSate++] = RxData;		//�����ݴ������ݰ������ָ��λ��
        
            }
        }
        else if(RxState == 2)
        {
            if(RxData == '\n')
            {
                RxState = 0;
                Serial_RxFlag= 1;
                Serial_RXPacket[pRxSate++] ='\0';

            }
          
        }
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);//���USART1��RXNE��־λ
    }
}

#else
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//�ж��Ƿ���USART1�Ľ����¼��������ж�
	{
		Serial_RxData = USART_ReceiveData(USART1);				//��ȡ���ݼĴ���������ڽ��յ����ݱ���
		Serial_RxFlag = 1;										//�ý��ձ�־λ����Ϊ1
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			//���USART1��RXNE��־λ
																//��ȡ���ݼĴ������Զ�����˱�־λ
																//����Ѿ���ȡ�����ݼĴ�����Ҳ���Բ�ִ�д˴���
	}
}


#endif