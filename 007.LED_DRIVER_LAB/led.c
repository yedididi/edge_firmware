#include "device_driver.h"

void LED_Init(void)
{
	/* 다음 코드는 수정하지 마시오 */
	Macro_Set_Bit(RCC->APB2ENR, 3);



}

void LED_Display(unsigned int num)
{


}

void LED_All_On(void)
{



}

void LED_All_Off(void)
{


}
