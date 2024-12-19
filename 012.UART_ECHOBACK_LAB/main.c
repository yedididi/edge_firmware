#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();
}

// void Main(void)
// {
// 	Sys_Init();
// 	Uart_Printf("UART Echo-Back Test\n");

// 	for(;;)
// 	{
// 		// 받은 글자를 다시 UART로 출력한다


// 	}
// }

void Main(void)
{
    Sys_Init();
    Uart_Printf("UART Echo-Back Test\n");
 
    for(;;)
    {
#if 0       
        for(;;) // 수신버퍼 들어오는거 대기
        {
            if(Macro_Check_Bit_Set(USART1->SR,5)) break;
        }
#endif
 
        while(  !Macro_Check_Bit_Set(USART1->SR,5) ); 
 
        char x = USART1->DR;
 
#if 0
        for(;;) // 송신버퍼 비는거 대기
        {
            if(Macro_Check_Bit_Set(USART1->SR,7)) break;
        }
#endif
        while(  !Macro_Check_Bit_Set(USART1->SR,7) ); 
 
        USART1->DR = x;
    }
}