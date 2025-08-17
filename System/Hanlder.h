#ifndef _HANDLER_H
#define _HANDLER_H
// uint16_t num;

#if 0



void TIM2_IRQHandler(void)
{
   if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //判断是否是定时器2中断
   {
   //  num++;
  Key_Tick();
  LED_Tick();
      TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //清除中断标志位
      //处理定时器2中断
   }
}

#endif

#endif 