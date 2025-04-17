/*  This file is part of: **STM32F4 Template Stack**_
     Copyright (c) 2025 Nico Jan Eelhart_
     This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
    
     Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
     https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_    */


#include "general.h"
#include "./system/startup-code/registers.h"
#include "app1/app1_main.h"

// Std includes
#include <stdlib.h>
#include <string.h>

// Project related defines
#define LEDDELAY        800000

/*
 	This part is from:
 	author: Furkan Cayci
	description: STM32F4   
		toggles LEDs on GPIOD Pins 12, 13, 14, 15 compatible STM32F4 Discovery board
   		reference document: RM0090

		In this template code, we will only turn on some LEDs which require at least
		RCC and GPIO registers.
		RCC is used to turn on the clock to the GPIOD module
		GPIOD is used to drive the LED pins  */


int app1_main(void)
{
	// enabling GPIOD peripheral clock
	// RCC_AHB1ENR |= (1 << 3);  // This(Reset and Clock Control)) interfers with debugger, you can NOT step through the code!

	// Each module is powered separately. In order to turn on a module
	// we need to enable the relevant clock.
	// Set Bit 3 to enable GPIOD clock in AHB1ENR
	// AHB1ENR: XXXX XXXX XXXX XXXX XXXX XXXX XXXX 1XXX
	RCC->AHB1ENR |= 0x00000008;

	// Another way to write a 1 to a bit location is to shift it that much
	// Meaning shift number 1, 3 times to the left. Which would result in
	// 0b1000 or 0x8
	// RCC->AHB1ENR |= (1 << 3);

	// In order to make a pin output, we need to write 01 to the relevant
	// section in MODER register
	// We first need to AND it to reset them, then OR it to set them.
	//                     bit31                                         bit0
	// MODER register bits : 01 01 01 01 XX XX XX XX XX XX XX XX XX XX XX XX
	//                      p15                                           p0

	GPIOD->MODER &= 0x00FFFFFF;   // Reset bits 31-24 to clear old values
	GPIOD->MODER |= 0x55000000;   // Set MODER bits to 01 (0101 is 5 in hex)

	// You can do the same setup with shifting
	// GPIOD->MODER &= ~(0xFF << 24);
	// GPIOD->MODER |=  (0x55 << 24);

	// Set Pins 12-15 to 1 to turn on all LEDs
	// ODR: 1111 XXXX XXXX XXXX
	GPIOD->ODR |= 0xF000;
	

	// We can do the same setup with shifting
	// GPIOD->ODR |= (0xF << 12);

	while(1){
		delay(LEDDELAY);
		
		GPIOD->ODR ^= 0xF000;  // Toggle LEDs
		//GPIOD->ODR |= 0xEFFF;
		//volatile uint32_t odr_value = GPIOD->ODR;		// Easy way to read ODR value		
	}

	__asm("NOP"); // Assembly inline can be used if needed
    return 0;
}

