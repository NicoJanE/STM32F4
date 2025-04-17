/* 

This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_		*/


/* Linker script for STM32F4-Discovery (STM32F407VGT6) */
MEMORY
{

  /* ROM for flashing your (barebone) program */	
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K		
			/*	
				1024K => 0x100000 (1024*1024 = 1048576d )  
				ROM BEGIN = 0x08000000	
				ROM END = 0x080FFFFF		*/		

  /* RAM For Heap data and your stack */	
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH =  128K	
    		/* 	128K  => 0x20000 (128*1024 = 131072d) 
				RAM BEGIN = 0x20000000 
				RAM END = 0x20020000 		*/
  
  /* Extra Core Coupled Memory64K SRAM. Faster,thigh coupled to CPU */
  CCMRAM (rw) : ORIGIN = 0x10000000, LENGTH = 64K    			
			/* 	64K  => 0x10000 (64*1024 = 65536d) 
				CCMRAM BEGIN = 0x10000000 
				CCMRAM END = 0x10010000 

				Sample 1: __attribute__((section(".ccmram"))) uint8_t buffer[1024];
				sample 2: __attribute__((section(".ccmram"))) void fast_function(void) {..
				Sample 3: __attribute__((section(".ccmram"))) static int some_data = 42;

			*/
}

/* Function handler that is called when device starts or resets, see startup.c for implementation  */
ENTRY(Reset_Handler)


SECTIONS
{
	/*
		ROM.
		- Contains program code (machine instructions) and read-only data (e.g., const variables, function pointers).
		- The .text section is the first section in the linker script and is placed in the FLASH memory region.
		-  KEEP  means that the linker will not remove it.	*/
	.text :
	{
		KEEP(*(.vectors)) /* Vector table */
		*(.text*)         /* Program code */
		*(.rodata*)       /* Read only data */
		 . = ALIGN(4);
	} > FLASH

	__etext = ALIGN (4); /* perhaps this can e removed */

	/* 
		- Contains initilized globals and static variables (Not part of the vector table)	
		- Placed in the FLASH memory region and is loaded into RAM at runtime( (see startup.c)).
		- The linker script specifies the location of the .data section in FLASH memory using the AT directive.
		- The AT directive specifies the location of the section in FLASH memory, while the > RAM directive specifies the location of the section in RAM.

		Note: We use .data : AT (__etext), not .data : AT > FLASH, because .data must be copied from Flash to RAM during startup	
																																	*/

	.data : AT (__etext)	/* Indicates data (rodata) is define  after flash(.text) data. Must be copied into RAM (startup.c) */
	{
		__data_start__ = .;
		*(vtable)
		*(.data*)         		/* Read-write initialized data */

		. = ALIGN(4);
		__data_end__ = .;

	} > RAM


	/* 
		- CCMRAM (Core Coupled Memory) is a special 64 KB high-speed RAM directly connected to the CPU
		- Can be used in C program for: Fast data, Performance critical code, DMA buffers, and interrupt handlers.
		- Use in C with __atrtribute__ for example:  __attribute__((section(".ccmram")))	*/
  	.ccmram :
    {
        *(.ccmram)       /* All code and data in the .ccmram section */
		 . = ALIGN(4);
    } > CCMRAM

	/* 	(Block Started by Symbol) 
		- Stores uninitialized global and static variables, initialized to zero at runtime.
		- Not part of binary image, but part of the ELF file.
		- The .bss section is not loaded into RAM, but the size of the section is stored in the ELF file.
		- The .bss section does not store values in Flash but reserves RAM space for uninitialized variables.
		- At runtime, the startup code zeroes out this section before the program starts.	*/
	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.bss*)       		/* Read-write zero initialized data, grows dynamically */

		. = ALIGN(4);
		__bss_end__ = .;	/* Used in syscalls.c*/		 
		_end = . ; 			/* End of .bss section in RAM and START of the heap (see syscalls.c, _sbrk implementation) */
	     
	} > RAM



	/* The stack is at the end the RAM, currently we use 4K for our  bare-metal program 
		- __StackTop is used in the startup code to initialize the stack pointer (see startup.c)		
																								   */

	__StackTop = ORIGIN(RAM) + LENGTH(RAM) - 4K;   	/* Reserve 4K for stack at the end of the RAM  */
		/* 
			STACK START = 0x2001F000 (0x20000000 + 0x20000  - 0x1000)
			END STACK = 0x20020000 (0x20000000 + 0x20000)                
		*/

 	/* End heap at stack start */
	__heap_end__ = __StackTop;  					

}


/*
	General References:
 
	Definitions used  in `syscalls.c`
		__heap_end__ is used in syscalls.c to implement the _sbrk function, which is used by malloc
		__bss_start__ and __bss_end__ are used in syscalls.c to implement the _sbrk function, which is used by malloc
		__data_start__ and __data_end__ are used in syscalls.c to implement the _sbrk function, which is used by malloc

	References with good explanation:
		https://interrupt.memfault.com/blog/how-to-write-linker-scripts-for-firmware#complete-linker-script		

	References about the STM32F4 Discovery board
		board: https://docs.zephyrproject.org/latest/boards/st/stm32f4_disco/doc/index.html						*/
