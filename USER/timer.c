#include "stm32f10x.h"
#include "timer.h"

extern u8 cnt;
extern u8 time_set_flag;
extern u8 WORK_TIME;

uint64_t xsec_clk=0;

void TIM2_Int_Init(u16 arr,u16 psc)
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //①时钟 TIM2 使能
//定时器 TIM2 初始化
TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载寄存器周期的值
TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置时钟频率除数的预分频值
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数
TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //②初始化 TIM2
TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE); //③允许更新中断
//中断优先级 NVIC 设置
NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //TIM2 中断
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //先占优先级 1 级
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //从优先级 3 级
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ 通道被使能
NVIC_Init(&NVIC_InitStructure); //④初始化 NVIC 寄存器
}

//定时器 2 中断服务程序⑥
void TIM2_IRQHandler(void) //TIM3 中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查 TIM2 更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //清除 TIM2 更新中断标志
		if(time_set_flag==0)
		{
			xsec_clk++;
			if(xsec_clk>(WORK_TIME*2-1))//每0.5s*WORKTIME*2,计数量cnt++
			{
				if(cnt<8)
				{
					cnt++;
				}
				else
				{
					cnt=0;
				}
				xsec_clk=0;
			}
		}
	}
}
