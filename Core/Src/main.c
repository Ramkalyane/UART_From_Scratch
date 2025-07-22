#include"stm32f4xx_hal.h"
#include"main.h"

void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);

UART_HandleTypeDef huart2;
int main(void)
{
	HAL_Init(); // Hardware init

	SystemClockConfig();
}


void SystemClockConfig(void)
{
	while(1);
}

//High level peripheral init
void UART2_Init(void)
{
	huart2.Instance        = USART2;  // this is macro refere to base address of pheripheral
	huart2.Init.BaudRate   = 15200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits   = UART_STOPBITS_1;
	huart2.Init.Parity     = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	huart2.Init.Mode       = UART_MODE_TX_RX;

	if(HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_handler();
	}
}

void Error_handler(void)
{
	while(1);
}
