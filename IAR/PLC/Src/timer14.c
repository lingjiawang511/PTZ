#include "timer14.h"
#include "rtc.h"
#include "tim.h"
#include "stmpe811.h"
#include "initial.h"
#include "core.h"

uint8_t DealNumber = 0; //the number of actual deal for pending deal

void Timer14_Init_Deal(uint16_t ShotTime, uint8_t DealNumb){ //0.0001 s per one

  TIM14->PSC = 8799;
  TIM14->ARR = ShotTime; //one second
  TIM14->DIER |= TIM_DIER_UIE; //interrupt enabled
  TIM14->CNT = 1;
  DealNumber = DealNumb;
  if(!DealNumb){
    NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn); //NVIC TIM6_DAC_IRQn enabled
  }
  else
    TIM14->CR1 |= TIM_CR1_CEN; // timer is on
  return;
}

void TIM14_IRQHandler(void){
  static uint32_t Counter = 0;
  TIM14->SR &= ~TIM_SR_UIF; //reset UIF
  TIM14->DIER &= ~TIM_DIER_UIE; //disable interrupt
  switch (DealNumber){
  case 0: 
    break;
  case 1: 
 //   if (RESmutex_1){
 //     Timer14_Init_Deal(100,1); 
 //     return;
 //   } 
   // RESmutex_1 = 1;
   // P_Touch_FreeIRQ();
  //  MX_Touch_Read();
 //   RESmutex_1 = 0;
    M_push(P_Touch_FreeIRQ);
    Timer14_Init_Deal(100,2);  
    break;

  case 2: 
 //   if (RESmutex_1){
 //     
 //     return;
 //   }

  M_push(MX_Touch_Read); 
  M_push(TouchScreen_Handle); 

    break;
  case 3: 
    DISP.ReleaseFlag = 1;   
    break;
  case 4:  

    break;
  case 5: 
    break;
  case 6: 
    break;
  case 7: 
    break;
  }  
  Counter++;
  return;
}
