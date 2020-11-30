#ifndef __hardware_H
#define __hardware_H
#endif 

#include <stm32f10x.h>

//#define WORK_TIME 60  //µ¥Î»Îªs

//void TIM3_Int_Init(u16 arr,u16 psc);
//void TIM3_IRQHandler(void);
void TIM2_Int_Init(u16 arr,u16 psc);
void TIM2_IRQHandler(void);
