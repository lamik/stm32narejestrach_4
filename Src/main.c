/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mateusz Salamon
 * @brief          : STM32 na Rejestrach
 ******************************************************************************
 ******************************************************************************

 	 	 	 	 https://msalamon.pl
 	 	 	 	 https://sklep.msalamon.pl
 	 	 	 	 https://kursstm32.pl
 	 	 	 	 https://stm32narejestrach.pl

 */
#include "main.h"

#define LD4_ON GPIOA->BSRR = GPIO_BSRR_BS5
#define LD4_OFF GPIOA->BSRR = GPIO_BSRR_BR5
#define LD4_TOGGLE GPIOA->ODR ^= GPIO_ODR_OD5

#define PC13 (1<<13)
#define BUTTON_PRESSED (!(GPIOC->IDR & PC13))

__IO uint32_t Tick;

void ConfigureLD4(void);
void Delay(uint32_t Delay_ms);
void ConfigureButton(void);

int main(void)
{

	// 1s = 12 000 000
	// 0,001 = X
	SysTick_Config(12000000 / 1000);

	ConfigureLD4();
	ConfigureButton();

    /* Loop forever */
	while(1)
	{
//      if(GPIOC->IDR & (1<<13))
//		if(GPIOC->IDR & GPIO_IDR_ID13)
//		if( BUTTON_PRESSED )
//		{
//			// Button pushed
//			LD4_ON;
//		}
//		else
//		{
//
//			// Button released
//			LD4_OFF;
//		}

		// Check if button was pressed
		if( BUTTON_PRESSED )
		{
			Delay(300); // Dummy debounce

			if( BUTTON_PRESSED ) // Check button again
			{
				// Toggle LED
				LD4_TOGGLE;
				
				while(BUTTON_PRESSED){} // Wait for button release
			}
		}

	}
}

void ConfigureLD4(void)
{
	// Enable Clock for PORTD
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

	// Configure GPIO Mode - Output
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
	GPIOA->MODER &= ~(GPIO_MODER_MODE5_1);

	// Configure Output Mode - Push-pull
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5);

	// Configure GPIO Speed - Low
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED5);

	// Configure Pull-up/Pull-down - no PU/PD
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5);
}

// PC13 - Button
// 0 - Pushed
// 1 - Released / Idle
void ConfigureButton(void)
{
	// Enable Clock for PORTC
	RCC->IOPENR |= RCC_IOPENR_GPIOCEN;

	// Configure GPIO Mode - Input
	GPIOC->MODER &= ~(GPIO_MODER_MODE13);
	
	// Configure Pull-up/Pull-down - no PU/PD
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD13);
}

void SysTick_Handler(void)
{
	Tick++; // Increase system timer
}

void Delay(uint32_t Delay_ms)
{
	uint32_t StartTime = Tick;

	while(Tick < (StartTime + Delay_ms))
	{
		// Just wait
	}
}






