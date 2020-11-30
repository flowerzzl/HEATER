#include "key.h"
#include "delay.h"
#include "ds3231.h"

static u8 key_up=1;//�������ɿ���־

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
	Gpio_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//��ʹ���������Ҳ�����ø�������
	Gpio_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&Gpio_InitStructure);
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA , ENABLE);
	Gpio_InitStructure.GPIO_Pin=GPIO_Pin_9;
	Gpio_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//��ʹ���������Ҳ�����ø�������
	Gpio_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&Gpio_InitStructure);
}

/*
u8 key_time_scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(WK_UP==1)return WKUP_PRES; 
	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	     
	return 0;// �ް�������
}
*/

void EXTI_INIT(void)
{
	  EXTI_InitTypeDef EXTI_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

//		GPIOB.0 �ж����Լ��жϳ�ʼ������   
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);

//  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY2
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�1������GPIOB.0Ϊ���ذ���������������ȼ� 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//  	NVIC_Init(&NVIC_InitStructure); 
	
	  //GPIOC.13 �ж����Լ��жϳ�ʼ������ 
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;	//ʱ���趨���밴��
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�2������GPIOC.13Ϊʱ���趨���������ȼ����ڿ��� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource14);//ʱ�����λѡ���

  	EXTI_InitStructure.EXTI_Line=EXTI_Line14;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�3������GPIOC.14Ϊʱ���趨λѡ�񰴼������ȼ�����ʱ���趨���밴�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource15);//ʱ������

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�3������GPIOC.15Ϊʱ�������������ȼ�����ʱ���趨���밴�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

        GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9);//�ٶȵ�λѡ���

  	EXTI_InitStructure.EXTI_Line=EXTI_Line9;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�3������GPIOA.19Ϊ�ٶȵ�λѡ��������ȼ�����ʱ���趨���밴�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
}

void EXTI9_5_IRQHandler(void)//�ٶȵ�λѡ���
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
	EXTI_ClearITPendingBit(EXTI_Line9); //���LINE13�ϵ��жϱ�־λ        
}


void EXTI15_10_IRQHandler(void)//ʱ���趨�������ʱ������
{
		//��ʱ���趨�����������
		if(KEY_TIME_SETTING==0)
		{
			delay_ms(10);//ȥ����
			if(KEY_TIME_SETTING==0)
			{
					set_flag = 1;
					get_show_time();
					min_time=calendar.min;
					sec_time=calendar.sec;
					hour_time=calendar.hour;
					EXTI_ClearITPendingBit(EXTI_Line13); //���LINE13�ϵ��жϱ�־λ
					return;
			}
		}
		
		//��ʱ�����λ��������
		if(key_up && KEY_TIME_BIT==0)
		{
				delay_ms(10);//ȥ����
				if(KEY_TIME_BIT==0)
				if(set_flag == 1)
				{
							time_set_bit_flag_1=((time_set_bit_flag_1+1)&0x01);//time_set_bit_flag_1==1ʱ��ʱ�����Ϊmin
							if(time_set_bit_flag_1==1)		//time_set_bit_flag_1==1ʱ��ʱ�����Ϊmin
							{
								//display_time(min_time);
							}
							else													//time_set_bit_flag_1==0ʱ��ʱ�����Ϊhour
							{
								//display_time(hour_time);
							}
							if(KEY_TIME_BIT==0)  key_up = 1;
				}
		}
		
		if(KEY_TIME_ADD==0)
		{
				delay_ms(10);//ȥ����
				if(KEY_TIME_ADD==0)
				{
						if(time_set_bit_flag_1==1)//��ʱ�޸ķ���
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
		EXTI_ClearITPendingBit(EXTI_Line14); //���LINE14�ϵ��жϱ�־λ�������Ƿ�ִ�ж�Ӧ�������־λ 
		EXTI_ClearITPendingBit(EXTI_Line15); 
}

	
	
	
	
	
	
	
/*	
	if(==0)
	{
//		time_set_flag=((time_set_flag+1)&0x01);	//ÿ�ΰ��°���time_set_flag���λ��ת
//		if(time_set_flag==0)
//		{
//			TIM_Cmd(TIM2, ENABLE);//��ʱ���趨״̬�ر���timer2���ڰ�����������״̬ʱӦ��
//		}
		set_flag=1;
	}
	EXTI_ClearITPendingBit(EXTI_Line13); //���LINE13�ϵ��жϱ�־λ 
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
  EXTI_ClearITPendingBit(EXTI_Line14); //���LINE14�ϵ��жϱ�־λ�������Ƿ�ִ�ж�Ӧ�������־λ 
	EXTI_ClearITPendingBit(EXTI_Line15); 
}
*/
