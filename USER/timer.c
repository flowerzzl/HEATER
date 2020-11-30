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
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //��ʱ�� TIM2 ʹ��
//��ʱ�� TIM2 ��ʼ��
TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ�ؼĴ������ڵ�ֵ
TIM_TimeBaseStructure.TIM_Prescaler =psc; //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM ���ϼ���
TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //�ڳ�ʼ�� TIM2
TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE); //����������ж�
//�ж����ȼ� NVIC ����
NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //TIM2 �ж�
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ� 1 ��
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ� 3 ��
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ ͨ����ʹ��
NVIC_Init(&NVIC_InitStructure); //�ܳ�ʼ�� NVIC �Ĵ���
}

//��ʱ�� 2 �жϷ�������
void TIM2_IRQHandler(void) //TIM3 �ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //��� TIM2 �����жϷ������
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //��� TIM2 �����жϱ�־
		if(time_set_flag==0)
		{
			xsec_clk++;
			if(xsec_clk>(WORK_TIME*2-1))//ÿ0.5s*WORKTIME*2,������cnt++
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
