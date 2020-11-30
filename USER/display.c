#include "stm32f10x.h"
#include "display.h"
#include "delay.h"
#include "timer.h"




void display_init(void)
{
	GPIO_InitTypeDef Gpio_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //复用功能时钟   (这句重点)  
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, DISABLE);	//SWJ完全失能(JTAG+SW-DP) 
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB , ENABLE);
	Gpio_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	Gpio_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	Gpio_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&Gpio_InitStructure);
	GPIO_WriteBit(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10,(BitAction)0);
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA , ENABLE);
	Gpio_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
	Gpio_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	Gpio_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&Gpio_InitStructure);
	GPIO_WriteBit(GPIOA,GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12,(BitAction)1);
}


void display_time(u8 time)
{
        u8 a,b,c,d,e,f;
	      a=(time&0x01)>>0;
			  b=(time&0x02)>>1;
				c=(time&0x04)>>2;
				d=(time&0x08)>>3;
				e=(time&0x10)>>4;
				f=(time&0x20)>>5;
        
        GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)a);
        GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)b);
        GPIO_WriteBit(GPIOB,GPIO_Pin_5,(BitAction)c);
        GPIO_WriteBit(GPIOB,GPIO_Pin_6,(BitAction)d);
        GPIO_WriteBit(GPIOB,GPIO_Pin_7,(BitAction)e);
        GPIO_WriteBit(GPIOB,GPIO_Pin_8,(BitAction)f);   	
}

