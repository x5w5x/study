#include"stm32f10x.h"

/**
 * @name: LightSensor_Init
 * @brief: 光敏传感器初始化
 * @param: void
 */
void LightSensor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/**
 * @name: LightSensor_Read
 * @brief: 读取光敏传感器数据（改一下就可以读取高低电平）
 * @param: void
 */
uint8_t LightSensor_Read(void)
{
    return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}