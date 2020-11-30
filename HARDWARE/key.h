#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 	 

//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
 

#define KEY_TIME_SETTING  	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡʱ���趨�����
#define KEY_TIME_BIT  			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//��ȡʱ���趨λѡ���
#define KEY_TIME_ADD   			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡʱ������
 

#define KEY_TIME_SETTING_PRES		1		//ʱ���趨�����������
#define KEY_TIME_BIT_PRES				2		//ʱ���趨λѡ���������
#define KEY_TIME_ADD_PRES				3		//ʱ������������

void KEY_Init(void);	//IO��ʼ��
u8 key_time_scan(u8 mode);	//����ɨ�躯��

#endif


extern u8 change_flag;
extern u8 time_set_flag;
extern u8 data_read;
extern u8 time_set_bit_flag_1;
extern u8 time_set_add_flag;
extern u8 set_flag;
extern u8 WORK_TIME;
extern u8 speed_rank;

extern u8 hour_time;
extern u8 min_time;
extern u8 sec_time;
extern u8 temp_hr;
extern u8 temp_min;
extern u8 temp_sec;
