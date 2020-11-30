#include "stm32f10x.h"
#include "DS3231.h"
#include "key.h"
#include "delay.h"
#include "DS3231.h"


u8 data_read=0;//每次从IO口读到的数据
u8 data_hr=0;
u8 data_min=0;
u8 change_flag=0;//加热顺序应该改变时，change_flag==1跳出循环节约时间
u8 time_set_flag=0;//time_set_flag==1时进入时间设定，计时暂停
u8 time_set_bit_flag_1=0;//时间调整位
u8 time_set_add_flag=0;//时间增键
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
u8 time_flag=0;//am，pm标志
uint32_t set_cnt=0;


int main(void) //还是要加禁止写，看到某次突然跳了2mins，不知道是芯片问题还是被写了+1
{	
	
	  //u8 temp;
	  SystemInit();  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
		DS3231_Init();
	  KEY_Init();
	  //led_init();
	  display_init();
	  //TIM3_Int_Init(5999,5999);//定时器0.5s中断,t=(5999+1)*(5999+1)/72M
	  TIM2_Int_Init(5999,5999);
		TIM_Cmd(TIM2, ENABLE);
	  //设置NVIC中断分组2:2位抢占优先级，2位响应优先级  
		EXTI_INIT();
	  while(1)
		{
			if(time_set_flag==0)//判断在时间设定状态还是正常运行状态，时间设定状态停止输出
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
																							 WORK_TIME=133;//上午12小时转36圈，每个输出高电平持续12*60*60/36/9=133s
																						 }
																						 else
																						 {
																							 WORK_TIME=200;//下午12小时转24圈，每个输出高电平持续12*60*60/24/9=200s
																							
																						 }																		         
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_10,(BitAction)0);
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_11,(BitAction)1);
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_12,(BitAction)1);break;
                                     case 1: 																			       
																			       if(time_flag==0)
																						 {
																							 WORK_TIME=133;//上午12小时转36圈，每个输出高电平持续12*60*60/36/9=133s
																							 
																						 }
																						 else
																						 {
																							 WORK_TIME=200;//下午12小时转24圈，每个输出高电平持续12*60*60/24/9=200s
																							
																						 }
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_10,(BitAction)1);
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_11,(BitAction)0);
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_12,(BitAction)1);break;
                                     case 2: 
																			 			 if(time_flag==0)
																						 {
																							 WORK_TIME=133;//上午12小时转36圈，每个输出高电平持续12*60*60/36/9=133s
																							 
																						 }
																						 else
																						 {
																							 WORK_TIME=200;//下午12小时转24圈，每个输出高电平持续12*60*60/24/9=200s
																						 }
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_10,(BitAction)1);
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_11,(BitAction)1);
                                             GPIO_WriteBit(GPIOA,GPIO_Pin_12,(BitAction)0);break;                                              
                                }
                                //display_time(hour_time,min_time,sec_time);
				if((hour_time>22)|(hour_time<11))
				{
					time_flag=0;
					if(!((temp_hr>22)|(temp_hr<11)))//刚进入hour_time<10状态,用于状态转换时清零cnt从头开始
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
				TIM_Cmd(TIM2, DISABLE);//时间设定状态下停止输出，timer2关闭
//				read_operation(SEC_READ_ADDR);
//				temp=data_read;
//				write_operation(SEC_WRITE_ADDR,(0x80|temp));//设定时间先暂停计时
				get_show_time();
				min_time=calendar.min;
				sec_time=calendar.sec;
				hour_time=calendar.hour;
				if(time_set_bit_flag_1==1)		//time_set_bit_flag_1==1时，时间调整为min
				{
					display_time(min_time);
				}
				else													//time_set_bit_flag_1==0时，时间调整为hour
				{
					display_time(hour_time);
				}
				//display_time(hour_time,min_time,sec_time);
				if(time_set_add_flag==1)
				{
					if(time_set_bit_flag_1==1)//此时修改小时
						{
							//read_operation(HR_READ_ADDR);                //确实需要进行时间设定再读时间，有时候只是无意按到时间设定，很快又会切换出去
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
				else					//按下时间设定进入按钮
				{
						if(set_cnt<250&&set_cnt>3)				//短按，时间调整位改变
						{
							time_set_bit_flag_1=((time_set_bit_flag_1+1)&0x01);
						}
						else															//长按，时间设定标志位改变
						{
							time_set_flag=((time_set_flag+1)&0x01);	
							if(time_set_flag==0)
							{
								TIM_Cmd(TIM2, ENABLE);//在时间设定状态关闭了timer2，在按键进入运行状态时应打开
							}
						}
						set_flag=0;
						set_cnt=0;
				}
				
			}*/
		}
}
