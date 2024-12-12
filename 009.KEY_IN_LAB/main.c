#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
}

/* Key 인식 */

#if 1

void Main(void)
{
	Sys_Init();
	Uart_Printf("KEY Input Test #1\n");

	// KEY[1:0], GPB[7:6]을 GPIO 입력으로 선언



	for(;;)
	{
		// KEY0이 눌렸으면 LED0를 ON, 안 눌렸으면 OFF



		// KEY1이 눌렸으면 LED1를 ON, 안 눌렸으면 OFF



	}
}

#endif

/* Key에 의한 LED Toggling */

#if 0

void Main(void)
{
	Sys_Init();
	Uart_Printf("KEY Input Toggling #1\n");


	// KEY[1:0], GPB[7:6]을 GPIO 입력으로 선언



	for(;;)
	{
		// KEY0가 눌릴때마다 LED0의 값을 Toggling



	}
}

#endif
