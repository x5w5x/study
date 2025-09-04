#include"stm32f10x.h"
#include "Delay.h"
uint16_t count=0;




/**
 * @brief    计数传感器初始化
 * @param    无
 * @retval   无
 * @note     引脚PB14
 * 
 */
void CountSensor_Init(void)
{
    //时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //使能GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能复用功能时钟
    //GPIO初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    //中断初始化
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);//选择外部中断线路
    //配置EXTI
   EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//上升沿下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    //配置NVIC
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //配置NVIC优先级分组
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//选择外部中断线路
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能中断
    NVIC_Init(&NVIC_InitStructure);

}
/**
 * @brief   获取计数值
 *  @param    无
 * @retval  uint16_t
 * @note     无
 * @return uint16_t 
 */
uint16_t GetCount(void)
{
    return count;
}


/**
 * @brief    计算计数值
 * @param    无
 * @retval   无
 * @note     无
 * 
 */
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)		//判断是否是外部中断14号线触发的中断
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			count++;					//计数值自增一次
		}
		EXTI_ClearITPendingBit(EXTI_Line14);		//清除外部中断14号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
}