#include "key.h"
#include "delay.h"
#include "ds3231.h"

static u8 key_up=1;//按键按松开标志

void KEY_Init(void)
{
	GPIO_InitTypeDef Gpio_InitStructure;
//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB , ENABLE);
//	Gpio_InitStructure.GPIO_Pin=GPIO_Pin_0;
//	Gpio_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
//	Gpio_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&Gpio_InitStructure);
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC , ENABLE);
	Gpio_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	Gpio_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//即使外加上拉，也不能用浮空输入
	Gpio_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&Gpio_InitStructure);
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA , ENABLE);
	Gpio_InitStructure.GPIO_Pin=GPIO_Pin_9;
	Gpio_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//即使外加上拉，也不能用浮空输入
	Gpio_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&Gpio_InitStructure);
}

/*
u8 key_time_scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(WK_UP==1)return WKUP_PRES; 
	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	     
	return 0;// 无按键按下
}
*/

void EXTI_INIT(void)
{
	  EXTI_InitTypeDef EXTI_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

//		GPIOB.0 中断线以及中断初始化配置   
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);

//  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY2
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级1，按键GPIOB.0为开关按键，具有最高优先级 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure); 
	
	  //GPIOC.13 中断线以及中断初始化配置 
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;	//时间设定进入按键
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2，按键GPIOC.13为时间设定按键，优先级低于开关 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource14);//时间调整位选择键

  	EXTI_InitStructure.EXTI_Line=EXTI_Line14;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级3，按键GPIOC.14为时间设定位选择按键，优先级低于时间设定进入按键 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource15);//时间增键

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级3，按键GPIOC.15为时间增按键，优先级低于时间设定进入按键 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

        GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9);//速度档位选择键

  	EXTI_InitStructure.EXTI_Line=EXTI_Line9;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级3，按键GPIOA.19为速度档位选择键，优先级低于时间设定进入按键 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
}

void EXTI9_5_IRQHandler(void)//速度档位选择键
{
	delay_ms(10)
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0)
	{
              if(speed_rank>1)
             {
                 speed_rank=0;   
             }
              else
             {
                 speed_rank=speed_rank+1;
             }
	}
	EXTI_ClearITPendingBit(EXTI_Line9); //清除LINE13上的中断标志位        
}


void EXTI15_10_IRQHandler(void)//时间设定进入键或时间增键
{
		//当时间设定进入键被按下
		if(KEY_TIME_SETTING==0)
		{
			delay_ms(10);//去抖动
			if(KEY_TIME_SETTING==0)
			{
					set_flag = 1;
					get_show_time();
					min_time=calendar.min;
					sec_time=calendar.sec;
					hour_time=calendar.hour;
					EXTI_ClearITPendingBit(EXTI_Line13); //清除LINE13上的中断标志位
					return;
			}
		}
		
		//当时间调整位键被按下
		if(key_up && KEY_TIME_BIT==0)
		{
				delay_ms(10);//去抖动
				if(KEY_TIME_BIT==0)
				if(set_flag == 1)
				{
							time_set_bit_flag_1=((time_set_bit_flag_1+1)&0x01);//time_set_bit_flag_1==1时，时间调整为min
							if(time_set_bit_flag_1==1)		//time_set_bit_flag_1==1时，时间调整为min
							{
								//display_time(min_time);
							}
							else													//time_set_bit_flag_1==0时，时间调整为hour
							{
								//display_time(hour_time);
							}
							if(KEY_TIME_BIT==0)  key_up = 1;
				}
		}
		
		if(KEY_TIME_ADD==0)
		{
				delay_ms(10);//去抖动
				if(KEY_TIME_ADD==0)
				{
						if(time_set_bit_flag_1==1)//此时修改分钟
						{
							if(min_time<59)
							{
								temp_min=min_time+1;
							}
							else
							{
								temp_min=0;
							}
							I2cByteWrite(MIN_ADDR,((temp_min/10<<4)&0x70)|((temp_min%10)&0x0f));
							//display_time(temp_min);
						}
						else
						{
							if(hour_time<23)
							{
								temp_hr=hour_time+1;
							}
							else
							{
								temp_hr=0;
							}
							I2cByteWrite(HR_ADDR,((temp_hr/10<<4)&0x70)|((temp_hr%10)&0x0f));
							//display_time(temp_hr);
						}
				}
		}
		EXTI_ClearITPendingBit(EXTI_Line14); //清除LINE14上的中断标志位，无论是否执行都应该清除标志位 
		EXTI_ClearITPendingBit(EXTI_Line15); 
}

	
	
	
	
	
	
	
/*	
	if(==0)
	{
//		time_set_flag=((time_set_flag+1)&0x01);	//每次按下按键time_set_flag最低位翻转
//		if(time_set_flag==0)
//		{
//			TIM_Cmd(TIM2, ENABLE);//在时间设定状态关闭了timer2，在按键进入运行状态时应打开
//		}
		set_flag=1;
	}
	EXTI_ClearITPendingBit(EXTI_Line13); //清除LINE13上的中断标志位 
	if(time_set_flag==1)
	{
//		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)==0)
//	  {
//		  time_set_bit_flag_1=((time_set_bit_flag_1+1)&0x01);
//	  }
	  if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)==0)
	  {
		  time_set_add_flag=1;
	  }
	}
  EXTI_ClearITPendingBit(EXTI_Line14); //清除LINE14上的中断标志位，无论是否执行都应该清除标志位 
	EXTI_ClearITPendingBit(EXTI_Line15); 
}
*/
