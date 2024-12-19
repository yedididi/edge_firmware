#include "device_driver.h"

#define TIM2_TICK		20					//usec,  앞으로 이것만 바꾸면 된다
#define TIM2_FREQ		(1000000.0/TIM2_TICK)	//Hz 
#define TIM2_ARR_MAX	0xFFFF
#define TIM2_1ms_PLS	(1000/TIM2_TICK)
//TIMXCLK

void TIM2_Stopwatch_Start(void)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	TIM2->PSC = (int)(TIMXCLK / TIM2_FREQ + 0.5) - 1;  //72M / 50k - 1
	
	// ARR 초기값 설정 => 최대값 0xFFFF 설정
	TIM2->ARR = TIM2_ARR_MAX;
	
	TIM2->EGR |= 1<<0;
	// UG 이벤트 발생


	// TIM2 CR1 설정: down count, one pulse
	// TIM2 start
	TIM2->CR1 = (1<<4) | (1<<3) | (1<<0);
}

unsigned int TIM2_Stopwatch_Stop(void)
{
	//unsigned int time;


	Macro_Clear_Bit(TIM2->CR1, 0);
	return (TIM2_ARR_MAX - TIM2->CNT) * TIM2_TICK;
	// TIM2 stop
	// CNT 초기 설정값 (0xffff)와 현재 CNT의 펄스수 차이를 구하고
	// 그 펄스수 하나가 20usec이므로 20을 곱한값을 time에 저장
	// 계산된 time 값을 리턴(단위는 usec)

}

void TIM2_Delay(int time)
{
	//timer on
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	TIM2->PSC = (int)(TIMXCLK / TIM2_FREQ + 0.5) - 1;

	// ARR 초기값 설정 => 요청한 time msec에 해당하는 초기값 설정, max 값을 넣으면 안된다 50 * time
	TIM2->ARR = time * TIM2_1ms_PLS;

	// UG 이벤트 발생
	Macro_Set_Bit(TIM2->EGR, 0);

	//uif  를 먼저 0으로 설정하고 uie를 enable
	// Update Interrupt Pending Clear uif 
	// Update Interrupt Enable uie
	Macro_Clear_Bit(TIM2->SR, 0);
	Macro_Set_Bit(TIM2->DIER, 0);

	// TIM2 start
	// TIM2 CR1 설정: down count, one pulse
	TIM2->CR1 = (1<<4) | (1<<3) | (1<<0);

	// Wait timeout for loop로  flag  기다린다. 
	for (;;)
	{
		if (Macro_Check_Bit_Set(TIM2->SR, 0))
			break;
	}

	// Stop and Power off
	Macro_Clear_Bit(TIM2->CR1, 0);
	Macro_Clear_Bit(TIM2->DIER, 0);
}

void TIM4_Repeat(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 2);

	// PSC(50KHz),  
	TIM4->PSC = (int)(TIMXCLK / TIM2_FREQ + 0.5) - 1;

	//ARR(reload시 값, time msec값, time * 50) 설정
	TIM4->ARR = time * TIM2_1ms_PLS;

	// UG 이벤트 발생
	Macro_Set_Bit(TIM4->EGR, 0);

	// Update Interrupt Pending Clear
	// Update Interrupt Enable
	Macro_Clear_Bit(TIM4->SR, 0);
	Macro_Set_Bit(TIM4->DIER, 0);

	// TIM4 start
	// TIM4 CR1: ARPE=0, down counter, repeat mode(not one shot)
	TIM4->CR1 = (1<<4) | (0<<3) | (1<<0);

}

int TIM4_Check_Timeout(void)
{
	// 타이머가 timeout 이면 1 리턴, 아니면 0 리턴, 1인 경우 클리어도 진행해줘야함함
	if (Macro_Check_Bit_Set(TIM4->SR, 0))
	{
		Macro_Clear_Bit(TIM4->SR, 0);
		return (1);
	}
	return (0);
}

void TIM4_Stop(void)
{
	Macro_Clear_Bit(TIM4->CR1, 0);
	Macro_Clear_Bit(TIM4->DIER, 0);
	Macro_Clear_Bit(RCC->APB1ENR, 2);
}

void TIM4_Change_Value(int time)
{
	TIM4->ARR = 50 * time;
}
