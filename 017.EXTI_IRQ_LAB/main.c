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

void Main(void)
{
	Sys_Init();
	Uart1_Printf("EXTI Test\n");

	// AFIO, Port-B Clock Enable
	Macro_Set_Bit(RCC->APB2ENR, 0);
	Macro_Set_Bit(RCC->APB2ENR, 3);

	// // PB[7:6]을 입력으로 선언
	Macro_Write_Block(GPIOB->CRL,0xff,0x44,24);

	// // PB[7:6]을 EXTI 소스로 설정하고 Falling edge 선택, EXTI[7:6] 인터럽트 허용
	Macro_Write_Block(AFIO->EXTICR[1],0xff,0x11,8); //6, 7번 대표를를 b포트로 선택

	EXTI->PR = (0x3<<6); //pending clear
	Macro_Write_Block(EXTI->FTSR,0x3,0x3,6); //

	// // EXTI[7:6] Pending Clear 및 NVIC의 인터럽트 Pending clear
	Macro_Write_Block(EXTI->IMR,0x3,0x3,6);

	NVIC_ClearPendingIRQ(23);
	NVIC_EnableIRQ(23);


	
	__enable_irq();


	for(;;)
	{
		LED_Display(1);
		TIM2_Delay(500);
		LED_Display(2);
		TIM2_Delay(500);
	}
}
