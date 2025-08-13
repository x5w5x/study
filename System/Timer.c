#include"stm32f10x.h"
#include"Timer.h"

/**
 * @breif 定时器初始化
 * @param 无
 * @retval 无
 *  1s=72000000/7200=10000
 * period=10000-1
 * prescaler=7200-1
 * 
 * 1ms=72000000/7200/10000
 * period=1000-1
 * prescaler=72-1
 */
//定时1000ms
void Timer_Init(void)
{
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //开启定时器2时钟
   TIM_InternalClockConfig(TIM2); //使用内部时钟
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //时钟分频
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数
   TIM_TimeBaseStructure.TIM_Period=TIM2_period; //计数器周期
   TIM_TimeBaseStructure.TIM_Prescaler=TIM2_prescaler; //预分频系数
   TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //重复计数器
   TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure); //初始化定时器2



   TIM_ClearFlag(TIM2,TIM_IT_Update); //清除定时器2中断标志位防止初始化进入中断

   TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //使能定时器2中断

   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组
   NVIC_InitTypeDef NVIC_InitStructure;
   NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //设置中断通道
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //设置抢占优先级
   NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //设置响应优先级
   NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //使能中断通道
   NVIC_Init(&NVIC_InitStructure); //初始化中断通道

   TIM_Cmd(TIM2,ENABLE); //启动定时器2
}
/*

*/
/**
 * @breif 外部时钟源定时器初始化
 * @param 无
 * @retval 无
 *    1s=72000000/7200=10000
 */

void Timer_ETRInit(void){
   

 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //开启定时器2时钟
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //开启GPIOA时钟

 GPIO_InitTypeDef GPIO_InitStructure;
 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//输入下拉
 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 GPIO_Init(GPIOA,&GPIO_InitStructure);

 TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0); //使用外部时钟内部时钟



   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //时钟分频
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数
   TIM_TimeBaseStructure.TIM_Period=10-1; //计数器周期
   TIM_TimeBaseStructure.TIM_Prescaler=1-1; //预分频系数
   TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //重复计数器
   TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure); //初始化定时器2



   TIM_ClearFlag(TIM2,TIM_IT_Update); 
   TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //使能定时器2中断

   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组
   NVIC_InitTypeDef NVIC_InitStructure;
   NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //设置中断通道
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //设置抢占优先级
   NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //设置响应优先级
   NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //使能中断通道
   NVIC_Init(&NVIC_InitStructure); //初始化中断通道

   TIM_Cmd(TIM2,ENABLE); //启动定时器2





}
// void TIM2_IRQHandler(void)
// {
//    if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //判断是否是定时器2中断
//    {
//     num++;
//       TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //清除中断标志位
//       //处理定时器2中断
//    }
// }