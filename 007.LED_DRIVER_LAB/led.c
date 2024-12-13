#include "device_driver.h"

void LED_Init(void)
{
	/* 이 부분은 수정하지 말 것 */
	Macro_Set_Bit(RCC->APB2ENR, 3);

	/* 매크로를 이용하여 초기에 LED 모두 OFF */
	Macro_Write_Block(GPIOB->CRH, 0xff, 0x66, 0);
	Macro_Write_Block(GPIOB->ODR, 0x3, 0x3, 8);
}

void LED_Display(unsigned int num)
{
	Macro_Write_Block(GPIOB->ODR, 0x3, Macro_Extract_Area(num, 0x3, 0), 8);
}

void LED_All_On(void)
{
	Macro_Write_Block(GPIOB->ODR, 0x3, 0x3, 8);
}

void LED_All_Off(void)
{
	Macro_Write_Block(GPIOB->ODR, 0x3, 0x0, 8);
}