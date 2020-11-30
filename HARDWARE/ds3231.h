#include <stm32f10x.h>
#include <sys.h>

#ifndef __DS3231_H__
#define __DS3231_H__



typedef struct 
{
	u8 hour;
	u8 min;
	u8 sec;			
	u8 w_year;
	u8  w_month;
	u8  w_date;
	u8  week;		 
}_calendar_obj;	
				 
extern _calendar_obj calendar;	//日历结构体
//extern u8 const mon_table[12];	//月份日期数据表

void DS3231_Init(void);
void get_show_time(void);      
//u8 RTC_Get_Week(u16 year,u8 month,u8 day);
void DS3231_Set(u8 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//设置时间	
void DS3231_Get(void);
void I2cByteWrite(u8 addr,u8 bytedata);
#endif

#define SEC_ADDR 		 0x00
#define MIN_ADDR     0x01
#define HR_ADDR      0x02
#define DATE_ADDR	   0x04
#define MONTH_ADDR	 0x05
#define YEAR_ADDR    0X06

#define DS3231_WriteAddress 0xD0   
#define DS3231_ReadAddress  0xD1
