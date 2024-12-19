#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();

	SCB->VTOR = 0x08003000;
	SCB->SHCSR = 0;
}

extern volatile int Key_Value;

void Main(void)
{
	Sys_Init();
	Uart1_Printf("USART1 IRQ Test\n");

	Key_ISR_Enable(1);

	//밑 두 줄은 사실 uart_init에서 다 한다다
	Macro_Set_Bit(RCC->APB2ENR, 2);
	Macro_Set_Bit(RCC->APB2ENR, 14);

	Macro_Set_Bit(USART1->CR1, 5);
	NVIC_ClearPendingIRQ(37);
	NVIC_EnableIRQ(37);

	for(;;)
	{
		if(Key_Value)
		{
			Uart1_Printf("KEY=%d\n", Key_Value);
			Key_Value = 0;
		}

		LED_Display(1);
		TIM2_Delay(100);
		LED_Display(2);
		TIM2_Delay(100);
	}
}
