#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
}

/* Key 인식 */

#if 0

void Main(void)
{
	Sys_Init();
	Uart_Printf("KEY Input Test #1\n");

	// KEY[1:0], GPB[7:6]을 GPIO 입력으로 선언
	Macro_Write_Block(GPIOB->CRL, 0xff, 0x44, 24);


	for(;;)
	{
		// KEY0이 눌렸으면 LED0를 ON, 안 눌렸으면 OFF
		LED_Display(Macro_Extract_Area(~(GPIOB->IDR), 0x3, 6));
		// KEY1이 눌렸으면 LED1를 ON, 안 눌렸으면 OFF



	}
}

#endif

/* Key에 의한 LED Toggling */

#if 1

void Main(void)
{
	Sys_Init();
	Uart_Printf("KEY Input Toggling #1\n");
	uint8_t interlock = 1;

	// KEY[1:0], GPB[7:6]을 GPIO 입력으로 선언
	Macro_Write_Block(GPIOB->CRL, 0xff, 0x44, 24);

	for(;;)
	{
		if ((interlock != 0) && Macro_Check_Bit_Clear(GPIOB->IDR, 6))
		{
			Macro_Invert_Bit(GPIOB->ODR, 8);
			interlock = 0;
		}
		else if ((interlock == 0) && Macro_Check_Bit_Set(GPIOB->IDR, 6))
			interlock = 1;
	}
}

#endif
