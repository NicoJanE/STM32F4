/* 

This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_		*/

#include "system/startup-code/startup.h"

#include "general.h"
#include "system/startup-code/registers.h"


/* -----------------------------------------------------------------------------------------------------------------
 Vector Table (Interrup handlers table)

	-	Specific for the ARM Cortex-M architecture.
  	- 	attribute keyword puts table in beginning of .vectors section which is the beginning of .text section in the linker script
	-	The *interrupt vector offsets* are defined by the ARM Cortex-M architecture, but the actual  *interrupt names* and the number
	 	of device-specific interrupts (beyond the first 15 entries) are vendor-specific."
	-	You can change function names or add vendor-specific interrupts below, following the order in your MCU’s datasheet.
	    
		💡	For STM32F407 - Vector table can be found on page 374 in rm0090, 
			 see: https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series/documentation.html

	Explanation (see numbers below) 
	1.	Place the to be defined 'interrupt vector table' section into this memory location (defined in linker script). 
		This is where the processor expects the 'interrupt vector table' which is loaded by the linker.
	2. 	Defines the function pointer to the 'interrupt vector table'. The const ensures the table cannot be modified.
		be changed. The function pointer defines an array of functions, each corresponding to an expected interrupt handler.
	3.	Starting here, we define the functions that each array entry points to. These should match the expected memory layout, 
		so the processor can jump to them when an exception occurs.
	4.	The first entry must be the initial stack pointer value. It is provided by the linker script as `__StackTop`, 
	   	and cast to `(unsigned long)` because the ARM expects this value as a literal address, not a pointer. This is then
	   	cast to `intfunc`, which is a pointer-to-function type.

	   	Note:	On x86/AMD architectures, types like void* or uintptr_t are more commonly used instead of `unsigned long` for 
				addresses.


	Handling other interrups
	Just like the 'Reset_Handler' assign a new function to the interrupt intialize the required registers and call
	the function for future processing
------------------------------------------------------------------------------------------------------------------- */

/* 
	typedef: intfunc
	Defines a function pointer type that matches the signature required by the interrupt vector table.
		- 	A const pointer to function (*const intfunc) taking no parameters and returning void.
		- 	For special cases like `__StackTop`, the address value parameter is casted when using `intfunc` to handle 
			the ARM requirments		*/
typedef void (* const intfunc)(void);	

__attribute__ ((section(".vectors")))		/*  1. 	vector is defined in linker script 	 */
void (* const vector_table[])(void) = {		/*	2. 	Constant array of function pointers	 */
											/*	3.	From here, define each interrupt function pointer handler in order  */	

	(intfunc)((unsigned long)&__StackTop),	/* 	4.	0x000 4. Initial Stack Pointer, casting the stack address to a function pointer:  *ptr(unsigned long)(void)  */											 
	Reset_Handler,                          /* 0x004 Reset          */	
	Default_Handler,                    	/* 0x008 NMI        	*/
	Default_Handler,                    	/* 0x00C HardFault	    */
	Default_Handler,                    	/* 0x010 MemManage     	*/
	Default_Handler,                    	/* 0x014 BusFault      	*/
	Default_Handler,                    	/* 0x018 UsageFault    	*/
	0,                                  	/* 0x01C Reserved      	*/
	0,                                  	/* 0x020 Reserved      	*/
	0,                                  	/* 0x024 Reserved      	*/
	0,                                  	/* 0x028 Reserved      	*/
	Default_Handler,                    	/* 0x02C SVCall        	*/
	Default_Handler,                    	/* 0x030 Debug Monitor 	*/
	0,                                  	/* 0x034 Reserved      	*/
	Default_Handler,                    	/* 0x038 PendSV        	*/
	Default_Handler                     	/* 0x03C SysTick,  last core exception handler, specified by the ARM architecture */
	                                    	/* ... Starting from here the items are specific for your hardware */
};	


/* -----------------------------------------------------------------------------------------------------------------
	Entry point for the program.
	-	Initializes data, bss sections and calls main function of the program.
 	-	It doesn't do any FPU initialization

		-	NVIC		->	Nested Vectored Interrupt Controller
			Decides which interrupts are enabled/disabled  ( NVIC_EnableIRQ(...) )
		- 	RCC 		->  Reset and Clock Control (HSE Ready, PLL lock)
		
------------------------------------------------------------------------------------------------------------------- */
 void Reset_Handler(void)
 {
     /* initialize data and bss sections */
     _init_data();
	 
	 /* Application specific initialization, is done in app[X]_factory.h, see function: initialize() */

     /* Call main function */
     main();
 
     /* Wait forever in case the code exit from main */
     for (;;);
 }
 

/* ---------------------------------------------------------------------------------------------------------------
    Initializes memory sections at startup:
    
    - Copies initialized data from its Load Memory Address (LMA, in ROM) to the Virtual Memory Address (VMA, in RAM)
    - Clears the .bss section by zero-initializing it

    This function is typically called from Reset_Handler() before main() is executed.

    Linker-defined symbols used:
        __etext         - End of the .text section (also start of initialized data in ROM)
        __data_start__  - Start of the .data section in RAM
        __data_end__    - End of the .data section in RAM
        __bss_start__   - Start of the .bss section in RAM
        __bss_end__     - End of the .bss section in RAM
--------------------------------------------------------------------------------------------------------------- */
void _init_data(void)
{
 	/* Symbols defined in the linker script*/
	extern unsigned long __etext, __data_start__, __data_end__, __bss_start__, __bss_end__;
	unsigned long *src = &__etext;
	unsigned long *dst = &__data_start__;

	/* Copy initialized data from ROM to RAM (.data section) */
	while (dst < &__data_end__)
		*dst++ = *src++;

	/* Zero-initialize the .bss (global and static variables) section	*/
	for (dst = &__bss_start__; dst< &__bss_end__; dst++)
		*dst = 0;
}



/* -----------------------------------------------------------------------------------------------------------------
	Default handler function
	-	 All the exceptions will hit here since,  they are all pointed to this function
------------------------------------------------------------------------------------------------------------------- */
void Default_Handler(void)
{
	for (;;);  			/* Wait forever	*/
}