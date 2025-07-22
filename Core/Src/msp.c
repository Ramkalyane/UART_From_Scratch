

#include"stm32f4xx_hal.h"
#include"stm32f4xx_hal_cortex.h"

//#define NVIC_PRIORITYGROUP_4 0x00000003U

void HAL_MspInit(void)
{
    // 1. Set priority grouping
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    // 2. Enable required system exceptions
    SCB->SHCSR |= 0x00070000; // Usage fault, Memory fault, Bus fault

    // 3. Set priority for system exceptions
    HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
    HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
    HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

//Low level initialization of peripherl
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart;
	// Enable clock for USART2 peripheral and GPIO peripheral

	__HAL_RCC_USART2_CLK_ENABLE();

	__HAL_RCC_GPIOA_CLK_ENABLE();
	// Do pin masking configuration

	//1.configure pin 2 as tx
	gpio_uart.Pin       = GPIO_PIN_2;
	gpio_uart.Mode      = GPIO_MODE_AF_PP;
	gpio_uart.Pull      = GPIO_PULLUP;
	gpio_uart.Speed     = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2; //USART_TX

	HAL_GPIO_Init(GPIOA, &gpio_uart);

	gpio_uart.Pin       = GPIO_PIN_3; //USART_RX

	HAL_GPIO_Init(GPIOA, &gpio_uart);

	//Enable IRQ and set priority

	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
}
