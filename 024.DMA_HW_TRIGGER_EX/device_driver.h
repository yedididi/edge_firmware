#include "stm32f10x.h"
#include "option.h"
#include "macro.h"
#include "malloc.h"

// Uart.c

#define Uart_Init			Uart1_Init
#define Uart_Send_Byte		Uart1_Send_Byte
#define Uart_Send_String	Uart1_Send_String
#define Uart_Printf			Uart1_Printf

extern void Uart1_Init(int baud);
extern void Uart1_Send_Byte(char data);
extern void Uart1_Send_String(char *pt);
extern void Uart1_Printf(char *fmt,...);
extern char Uart1_Get_Char(void);
extern char Uart1_Get_Pressed(void);
extern void Uart1_RX_Interrupt_Enable(int en);
extern void Uart1_Wait_for_TX_Complete(void);

// Led.c

extern void LED_Init(void);
extern void LED_Display(unsigned int num);
extern void LED_All_On(void);
extern void LED_All_Off(void);

// Clock.c

extern void Clock_Init(void);

// Key.c

extern void Key_Poll_Init(void);
extern int Key_Get_Pressed(void);
extern void Key_Wait_Key_Released(void);
extern int Key_Wait_Key_Pressed(void);
extern void Key_ISR_Enable(int en);

// SysTick.c

extern void SysTick_Run(unsigned int msec);
extern int SysTick_Check_Timeout(void);
extern unsigned int SysTick_Get_Time(void);
extern unsigned int SysTick_Get_Load_Time(void);
extern void SysTick_Stop(void);
extern void SysTick_OS_Tick(unsigned int msec);

// Timer.c

extern void TIM2_Delay(int time);
extern void TIM2_Stopwatch_Start(void);
extern unsigned int TIM2_Stopwatch_Stop(void);
extern void TIM4_Repeat(int time);
extern int TIM4_Check_Timeout(void);
extern void TIM4_Stop(void);
extern void TIM4_Change_Value(int time);
extern void TIM3_Out_Init(void);
extern void TIM3_Out_Freq_Generation(unsigned short freq);
extern void TIM3_Out_Stop(void);
extern void TIM4_Repeat_Interrupt_Enable(int en, int time);

// DMA.c

struct _DMA_CCR_ST
{
  unsigned int temp : 4;
  unsigned int dir : 1;
  unsigned int circ : 1;
  unsigned int pinc : 1;
  unsigned int minc : 1;
  unsigned int psize : 2;
  unsigned int msize : 2;
  unsigned int pl : 2;
  unsigned int m2m : 1;
};

union _DMA_CCR_UNI
{
  struct _DMA_CCR_ST st_data;
  unsigned int ui_data;
};

#define DMA_STATUS_READY			(0)
#define DMA_STATUS_RUN				(1)
#define DMA_STATUS_COMPLETE			(2)
#define DMA_STATUS_HALFTRANSFERED	        (3)
#define DMA_STATUS_ERROR			(4)

#define	DMA_SIZE_8BIT				(0x0)
#define	DMA_SIZE_16BIT				(0x1)
#define	DMA_SIZE_32BIT				(0x2)

#define DMA_PL_LOW				(0x0)
#define DMA_PL_MEDIUM				(0x1)
#define DMA_PL_HIGH				(0x2)
#define DMA_PL_VERYHIGH				(0x3)

#define DMA_DIR_P2M				(0x0)
#define DMA_DIR_M2P				(0x1)

#define DMA_TRIGGER_HW				(0x0)
#define DMA_TRIGGER_SW				(0x1)

#define DMA_ADDR_FIX				(0x0)
#define DMA_ADDR_INC				(0x1)

#define DMA_CIRCULAR_DIS			(0x0)
#define DMA_CIRCULAR_EN				(0x1)

extern void DMA1_Ch_Init(int ch, void* maddr, void* paddr, union _DMA_CCR_UNI ccr, unsigned int tr_cnt);
extern unsigned int DMA1_Get_Status(int ch);
extern void DMA1_Start(int ch);
extern void DMA1_Stop(int ch);
extern void DMA1_ISR_Enable(int ch, unsigned int tei, unsigned int hti, unsigned int tci);
extern void DMA1_Set_Status(int ch, unsigned int status);
