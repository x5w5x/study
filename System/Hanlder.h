#ifndef _HANDLER_H
#define _HANDLER_H
// uint16_t num;

#if 0



void TIM2_IRQHandler(void)
{
   if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //�ж��Ƿ��Ƕ�ʱ��2�ж�
   {
   //  num++;
  Key_Tick();
  LED_Tick();
      TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //����жϱ�־λ
      //����ʱ��2�ж�
   }
}

#endif

#endif 