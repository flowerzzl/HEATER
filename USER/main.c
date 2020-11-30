#include "stm32f10x.h"
#include "DS3231.h"
#include "key.h"
#include "delay.h"
#include "DS3231.h"


u8 data_read=0;//ÿ�δ�IO�ڶ���������
u8 data_hr=0;
u8 data_min=0;
u8 change_flag=0;//����˳��Ӧ�øı�ʱ��change_flag==1����ѭ����Լʱ��
u8 time_set_flag=0;//time_set_flag==1ʱ����ʱ���趨����ʱ��ͣ
u8 time_set_bit_flag_1=0;//ʱ�����λ
u8 time_set_add_flag=0;//ʱ������
unsigned long time_delay=0;
u8 hour_time=0;
u8 min_time=0;
u8 sec_time=0;
u8 temp_hr=0;
u8 temp_min=0;
u8 temp_sec=0;
u8 temp_time_set_flag=0;
//u8 half_sec_flag=0;
u8 sec_1=0;
u8 flash_flag=0;
u8 cnt=0;
u8 set_flag=0;
u8 WORK_TIME=30;
u8 speed_rank=0;
u8 time_flag=0;//am��pm��־
uint32_t set_cnt=0;


int main(void) //����Ҫ�ӽ�ֹд������ĳ��ͻȻ����2mins����֪����оƬ���⻹�Ǳ�д��+1
{	
	
	  //u8 temp;
	  SystemInit();  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
		DS3231_Init();
	  KEY_Init();
	  //led_init();
	  display_init();
	  //TIM3_Int_Init(5999,5999);//��ʱ��0.5s�ж�,t=(5999+1)*(5999+1)/72M
	  TIM2_Int_Init(5999,5999);
		TIM_Cmd(TIM2, ENABLE);
	  //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�  
		EXTI_INIT();
	  while(1)
		{
			if(time_set_flag==0)//�ж���ʱ���趨״̬������������״̬��ʱ���趨״ֹ̬ͣ���
			{
				
				display_time(0);
				get_show_time();
				hour_time=calendar.hour;
				min_time=calendar.min;
				sec_time=calendar.sec;
				switch(speed_rank)
                                { 
                                     case 0: 
																			       if(time_flag==0)
																						 {
																							 WORK_TIME=133;//����12Сʱת36Ȧ��ÿ������ߵ�ƽ����12*60*60/36/9=133s
																						 }
																						 else
																						 {
																							 WORK_TIME=200;//����12Сʱת24Ȧ��ÿ������ߵ�ƽ����12*60*60/24/9=200s
																							
																						 }																		         
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_10,(BitAction)0);
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_11,(BitAction)1);
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_12,(BitAction)1);break;
                                     case 1: 																			       
																			       if(time_flag==0)
																						 {
																							 WORK_TIME=133;//����12Сʱת36Ȧ��ÿ������ߵ�ƽ����12*60*60/36/9=133s
																							 
																						 }
																						 else
																						 {
																							 WORK_TIME=200;//����12Сʱת24Ȧ��ÿ������ߵ�ƽ����12*60*60/24/9=200s
																							
																						 }
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_10,(BitAction)1);
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_11,(BitAction)0);
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_12,(BitAction)1);break;
                                     case 2: 
																			 			 if(time_flag==0)
																						 {
																							 WORK_TIME=133;//����12Сʱת36Ȧ��ÿ������ߵ�ƽ����12*60*60/36/9=133s
																							 
																						 }
																						 else
																						 {
																							 WORK_TIME=200;//����12Сʱת24Ȧ��ÿ������ߵ�ƽ����12*60*60/24/9=200s
																						 }
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_10,(BitAction)1);
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_11,(BitAction)1);
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_12,(BitAction)0);break;                                              
                                }
                                //display_time(hour_time,min_time,sec_time);
				if((hour_time>22)|(hour_time<11))
				{
					time_flag=0;
					if(!((temp_hr>22)|(temp_hr<11)))//�ս���hour_time<10״̬,����״̬ת��ʱ����cnt��ͷ��ʼ
					{
						cnt=0;
					}
					switch(cnt)
					{
						case 0:pw_ctl(ctl_am_1);break;
						case 1:pw_ctl(ctl_am_2);break;
            case 2:pw_ctl(ctl_am_3);break;
						case 3:pw_ctl(ctl_am_4);break;
            case 4:pw_ctl(ctl_am_5);break;
					  case 5:pw_ctl(ctl_am_6);break;
						case 6:pw_ctl(ctl_am_7);break;
						case 7:pw_ctl(ctl_am_8);break;
						case 8:pw_ctl(ctl_am_9);break;		
					}
				}
				else
				{
					time_flag=1;
					if(!((temp_hr<=22)&(temp_hr>=11)))
					{
						cnt=0;
					}
					switch(cnt)
					{
						case 0:pw_ctl(ctl_pm_1);break;
						case 1:pw_ctl(ctl_pm_2);break;
            case 2:pw_ctl(ctl_pm_3);break;
						case 3:pw_ctl(ctl_pm_4);break;
            case 4:pw_ctl(ctl_pm_5);break;
					  case 5:pw_ctl(ctl_pm_6);break;
						case 6:pw_ctl(ctl_pm_7);break;
						case 7:pw_ctl(ctl_pm_8);break;
						case 8:pw_ctl(ctl_pm_9);break;		
					}
				}
				temp_hr=hour_time;
			}
			else
			{
				pw_ctl(0);
                                GPIO_WriteBit(GPIOA,GPIO_Pin_10,(BitAction)1);
                                GPIO_WriteBit(GPIOA,GPIO_Pin_11,(BitAction)1);
                                GPIO_WriteBit(GPIOA,GPIO_Pin_12,(BitAction)1);
				TIM_Cmd(TIM2, DISABLE);//ʱ���趨״̬��ֹͣ�����timer2�ر�
//				read_operation(SEC_READ_ADDR);
//				temp=data_read;
//				write_operation(SEC_WRITE_ADDR,(0x80|temp));//�趨ʱ������ͣ��ʱ
				get_show_time();
				min_time=calendar.min;
				sec_time=calendar.sec;
				hour_time=calendar.hour;
				if(time_set_bit_flag_1==1)		//time_set_bit_flag_1==1ʱ��ʱ�����Ϊmin
				{
					display_time(min_time);
				}
				else													//time_set_bit_flag_1==0ʱ��ʱ�����Ϊhour
				{
					display_time(hour_time);
				}
				//display_time(hour_time,min_time,sec_time);
				if(time_set_add_flag==1)
				{
					if(time_set_bit_flag_1==1)//��ʱ�޸�Сʱ
						{
							//read_operation(HR_READ_ADDR);                //ȷʵ��Ҫ����ʱ���趨�ٶ�ʱ�䣬��ʱ��ֻ�����ⰴ��ʱ���趨���ܿ��ֻ��л���ȥ
						  //hour_time=((data_read&0x70)>>4)*10+(0x0f&data_read);
							if(min_time<59)
							{
								temp_min=min_time+1;
							}
							else
							{
								temp_min=0;
							}
							I2cByteWrite(MIN_ADDR,((temp_min/10<<4)&0x70)|((temp_min%10)&0x0f));
							//write_operation(MIN_WRITE_ADDR,((temp_min/10<<4)&0x70)|((temp_min%10)&0x0f));
							//display_time(temp_min);
						}
			      else
						{
							//read_operation(MIN_READ_ADDR);
						  //min_time=((data_read>>4)&0x07)*10+(0x0f&data_read);
							if(hour_time<23)
							{
								temp_hr=hour_time+1;
							}
							else
							{
								temp_hr=0;
							}
							//temp_min=min_time+1;
							I2cByteWrite(HR_ADDR,((temp_hr/10<<4)&0x70)|((temp_hr%10)&0x0f));
							//write_operation(HR_WRITE_ADDR,((temp_hr/10<<4)&0x70)|((temp_hr%10)&0x0f));
							//display_time(temp_hr);
						}
						time_set_add_flag=0;
				}						
			}	
			
			
			
			
			
			/*
			if(set_flag==1)
			{
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0)
				{
					set_cnt++;
				}
				else					//����ʱ���趨���밴ť
				{
						if(set_cnt<250&&set_cnt>3)				//�̰���ʱ�����λ�ı�
						{
							time_set_bit_flag_1=((time_set_bit_flag_1+1)&0x01);
						}
						else															//������ʱ���趨��־λ�ı�
						{
							time_set_flag=((time_set_flag+1)&0x01);	
							if(time_set_flag==0)
							{
								TIM_Cmd(TIM2, ENABLE);//��ʱ���趨״̬�ر���timer2���ڰ�����������״̬ʱӦ��
							}
						}
						set_flag=0;
						set_cnt=0;
				}
				
			}*/
		}
}
