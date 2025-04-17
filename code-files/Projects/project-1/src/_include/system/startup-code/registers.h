/* 

This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_		*/


#ifndef REGISTERS_H
#define REGISTERS_H

/*  
=================================================================================================================================================================================
=   General description                                                                                      																	=
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
PURPOSE
	- Define own peripherals names. For learning purpose, not using CMSIS header file (which containe the definitions for hardware address). 
	- Specific register addresses for the STM32F4xx micro-controller
	- Register definitions for the STM32F4xx PERIPHERALS (generates interrupt request), PERIPHERALS:		

		- GPIO				-> General-purpose input/output. 	Used for: Leds and buttons. 							Related: RCC, EXTI
		- USART				-> Serial communication interface. 	Used for: Lcommunication with; PC's, GPS  				Related: RCC, EXTI
		- SPI				-> Serial Peripheral Interface.		Used for: Communicate with displays,memory, sensors		Related: RCC, DMA, GPIO
		- I2C				-> Inter-Integrated Circuit.		Used for: Sensors, EEPROMs, RTC chips 					Related: RCC
		- ADC				-> Analog-to-Digital Converter		Used for: Read analog signals like temperature			Related: RCC, DMA
		- DAC				-> Digital-to-Analog Converter.		Used for: Audio, analog control signals 				Related: RCC
		- Timers (TIMx)		-> Timing, PWM, input capture.		Used for: delays, PWM for motors/LEDs					Related: RCC, NVIC, GPIO
		- SysTick			-> System timer (core peripheral)	Used for: RTOS, delay loops								Related: NVIC 
		- RTC				-> Real-Time Clock.					Used for: Keep time across resets/power-off				Related: 
		- EXTI				-> External Interrupt Controller	Used for: Generate interrupts from GPIO 				Related: NVIC, GPIO
		- DMA				-> Direct Memory Access.			Used for: Transfer data without 						Related: RCC, NVIC (optional),ADC, SPI, etc.
		- USB OTG FS/HS		-> USB Device or Host.				Used for: USB communication								Related: RCC, GPIO (specific pins), NVIC
		- FSMC	 			-> Interface ext. mem.(LCD or SRAM)	Used for: Advanced external memory/mapped display		Related: RCC, GPIO (dedicated pins), 
		- SDIO				-> ISD card interface.				Used for: Filesystem/logging support via SD card		Related: RCC, GPIO, DMA (optional)
		- CAN				-> Controller Area Network			Used for: Automotive or industrial communication		Related: RCC, GPIO, NVIC
		-*Ethernet (MAC)	-> Network communication.			Used for: Network communication							Related: RCC, External PHY, RMII pins
		- CRC				-> Cyclic Redundancy Check			Used for: Data integrity checking						Related:
		- WWDG/IWDG			-> Watchdogs.						Used for: Reset system if software hangs				Related: 
		- COMP/OPAMP		-> Comparators / Amplifiers.		Used for: Analog signal conditioning					Related: 
		- 					-> Inter-Integrated Circuit.		Used for: 												Related: RCC

			* Not available on Discovery(No External PHY) only: F407ZG

		
	- Definitions for other NONE PERIPHERALS (most ARM generic)

		- RCC (Reset and Clock Control, STM32 specific) -> Enables/disables clocks to all peripherals/system components.	Remark: Must ENABLE for ALL peripheral befor use
		- NVIC (Nested Vectored Interrupt Controller)	-> Controls which interrupts are enabled, prioritized, or pending	Remark:
		- SCB (System Control Block)					-> Controls core exceptions (HardFault, SysTick, etc.)				Remark: system-level configuration 
		- SysTick										-> A special timer in the Cortex-M core								Remark: delays, or RTOS tick
		- FPU (Floating Point Unit)						-> floating-point math efficiently									Remark: enabled in some MCUs by default
		- MPU (Memory Protection Unit)					-> Segments memory access rules										Remark: used for security, RTOS, etc.
		- VTOR (Vector Table Offset Register)			-> Allows moving the interrupt vector table							Remark: Used in bootloaders, dynamic loading systems
		- CMSIS											-> Cortex Microcontroller Software Interface Standard				Remark: A vendor-independent API.
		- Startup code									-> Assembly or C code that runs before main()						Remark: Init. stack, vector table, .data, .bss sections


	- Defines Typed access to memory-mapped registers
		- Create a struct with Register names (every item has an ofset)
		- Make sure to define a pointer to this structure that starts at the base address
			- #define MY_GPIOD ((My_struct_t *) 0x40020C00)
		- After that you can acces the items like: MY_GPIOD->struct_item
	

	References
	How to get information without studying the 1750 pages from the reference manual
	- https://github.com/STMicroelectronics
	- Search for:'STM32 DAC application note'  
	  - at :https://www.st.com/content/st_com/en.html
	  - or at google.com
		Note that application notes start with: ANxxxx
	- Also the STM32CubeF4 framework contains some good examples
	- YouTube tutorials (STM32 DAC bare metal example, STM32F4 DAC register init, )
	- Use the official reference to fillin the details when needed, found here: https://www.st.com/resource/en/reference_manual/rm0090-stm32f405415-stm32f407417-stm32f427437-and-stm32f429439-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#include <stdio.h>
#include<stdint.h>


/*-----------------------------------------------------------------------------------------------------------------  
=   USAGE: Register Addresses                                                                                     =
------------------------------------------------------------------------------------------------------------------- 
 Define the base addresses for peripherals used  You can calculate the addresses relative to periph_base, 
 or directly assign them Base addresses can be found on page 64 in RM0090
------------------------------------------------------------------------------------------------------------------- */
#define PERIPH_BASE     ((uint32_t) 0x40000000)
#define USART_BASE  	((uint32_t) 0x40004400)
#define GPIOA_BASE    	((uint32_t) 0x40020000 ) 			// Base address of GPIOA
#define GPIOD_BASE      (PERIPH_BASE + 0x20C00) 			// GPIOD base address is 0x40020C00
#define RCC_BASE        (PERIPH_BASE + 0x23800) 			// RCC base address is 0x40023800




/* ----------------------------------------------------------------------------------------------------------------
=   USAGE: Register Addresses — RCC                                                                                    =
-------------------------------------------------------------------------------------------------------------------

    Define the 'typed access to memory-mapped registers' struct for: RCC

    Usually, these definitions are provided by the processor manufacturer (via CMSIS).
    Here, we define them ourselves for a bare-metal implementation.
    Make sure to use 'volatile' to prevent the compiler from optimizing out hardware access.

    References:
        - rm0090: Reference Manual for STM32F405/407 processors.
          The RCC and GPIO sections (especially toward the end) list the register layout.
        - RCC (Reset and Clock Control) module starts on page 267 in rm0090.

------------------------------------------------------------------------------------------------------------------- */
typedef struct {
	volatile uint32_t CR;         /* Address offset: 0x00 */
	volatile uint32_t PLLCFGR;    /* Address offset: 0x04 */
	volatile uint32_t CFGR;       /* Address offset: 0x08 */
	volatile uint32_t CIR;        /* Address offset: 0x0C */
	volatile uint32_t AHB1RSTR;   /* Address offset: 0x10 */
	volatile uint32_t AHB2RSTR;   /* Address offset: 0x14 */
	volatile uint32_t AHB3RSTR;   /* Address offset: 0x18 */
	volatile uint32_t RESERVED1;  /* Address offset: 0x1C */
	volatile uint32_t APB1RSTR;   /* Address offset: 0x20 */
	volatile uint32_t APB2RSTR;   /* Address offset: 0x24 */
	volatile uint32_t RESERVED2;  /* Address offset: 0x28 */
	volatile uint32_t RESERVED3;  /* Address offset: 0x2C */
	volatile uint32_t AHB1ENR;    /* Address offset: 0x30 */
	volatile uint32_t AHB2ENR;    /* Address offset: 0x34 */
	volatile uint32_t AHB3ENR;    /* Address offset: 0x38 */
	volatile uint32_t RESERVED4;  /* Address offset: 0x3C */
	volatile uint32_t APB1ENR;    /* Address offset: 0x40 */
	volatile uint32_t APB2ENR;    /* Address offset: 0x44 */
	volatile uint32_t RESERVED5;  /* Address offset: 0x48 */
	volatile uint32_t RESERVED6;  /* Address offset: 0x4C */
	volatile uint32_t AHB1LPENR;  /* Address offset: 0x50 */
	volatile uint32_t AHB2LPENR;  /* Address offset: 0x54 */
	volatile uint32_t AHB3LPENR;  /* Address offset: 0x58 */
	volatile uint32_t RESERVED7;  /* Address offset: 0x5C */
	volatile uint32_t APB1LPENR;  /* Address offset: 0x60 */
	volatile uint32_t APB2LPENR;  /* Address offset: 0x64 */
	volatile uint32_t RESERVED8;  /* Address offset: 0x68 */
	volatile uint32_t RESERVED9;  /* Address offset: 0x6C */
	volatile uint32_t BDCR;       /* Address offset: 0x70 */
	volatile uint32_t CSR;        /* Address offset: 0x74 */
	volatile uint32_t RESERVED10; /* Address offset: 0x78 */
	volatile uint32_t RESERVED11; /* Address offset: 0x7C */
	volatile uint32_t SSCGR;      /* Address offset: 0x80 */
	volatile uint32_t PLLI2SCFGR; /* Address offset: 0x84 */
} RCC_type;


/* ----------------------------------------------------------------------------------------------------------------
=   USAGE: Register Addresses — GPIO                                                                               =
-------------------------------------------------------------------------------------------------------------------

    Define the 'typed access to memory-mapped registers' struct for: GPIO

    Normally, these register definitions are provided by the processor manufacturer (via CMSIS).
    Here, we define them ourselves for a bare-metal implementation to better understand
    the hardware layout and memory-mapped register model.

    Always mark hardware registers as 'volatile' to prevent the compiler from optimizing out
    reads/writes during code generation.

    References:
        - rm0090: Reference Manual for STM32F405/407 processors
        - General-purpose I/Os (GPIO) module — starts at page 288 in rm0090
          Register map is detailed at the end of the GPIO chapter.

------------------------------------------------------------------------------------------------------------------- */
typedef struct {
    volatile uint32_t MODER;      /* Address offset: 0x00 - Mode register */
    volatile uint32_t OTYPER;     /* Address offset: 0x04 - Output type register */
    volatile uint32_t OSPEEDR;    /* Address offset: 0x08 - Output speed register */
    volatile uint32_t PUPDR;      /* Address offset: 0x0C - Pull-up/pull-down register */
    volatile uint32_t IDR;        /* Address offset: 0x10 - Input data register */
    volatile uint32_t ODR;        /* Address offset: 0x14 - Output data register */
    volatile uint32_t BSRR;       /* Address offset: 0x18 - Bit set/reset register */
    volatile uint32_t LCKR;       /* Address offset: 0x1C - Configuration lock register */
    volatile uint32_t AFRL;       /* Address offset: 0x20 - Alternate function low register */
    volatile uint32_t AFRH;       /* Address offset: 0x24 - Alternate function high register */
} GPIO_type;


/* ----------------------------------------------------------------------------------------------------------------
=   USAGE: Register Addresses — USART                                                                              =
-------------------------------------------------------------------------------------------------------------------

    Define the 'typed access to memory-mapped registers' struct for: USART

    Normally, these definitions are provided by the processor manufacturer (via CMSIS).
    Here, we define them ourselves for a bare-metal implementation to gain more insight
    into low-level peripheral access.

    Always mark hardware registers as 'volatile' to prevent the compiler from optimizing out
    reads and writes to these memory-mapped regions.

    References:
        - rm0090: Reference Manual for STM32F405/407 processors
        - Universal synchronous asynchronous receiver transmitter (USART) module
          starts on page 981 in rm0090
          Register information starts from page 1756 (Section 30.6)

------------------------------------------------------------------------------------------------------------------- */
typedef struct {
    volatile uint32_t SR;       /* Status register                      - Offset: 0x00 */
    volatile uint32_t DR;       /* Data register                        - Offset: 0x04 */
    volatile uint32_t BRR;      /* Baud rate register                   - Offset: 0x08 */
    volatile uint32_t CR1;      /* Control register 1                   - Offset: 0x0C */
    volatile uint32_t CR2;      /* Control register 2                   - Offset: 0x10 */
    volatile uint32_t CR3;      /* Control register 3                   - Offset: 0x14 */
    volatile uint32_t GTPR;     /* Guard time and prescaler register    - Offset: 0x18 */
} USART_type;


/* ----------------------------------------------------------------------------------------------------------------
=   PURPOSE: Create pointers to the register structures (peripheral base addresses)                                =
-------------------------------------------------------------------------------------------------------------------

    These macros allow access to peripheral registers using the 'typed access to memory-mapped registers' structs.
    Each macro casts the base address of the peripheral to a pointer of the corresponding structure type.

    Access individual registers using the '->' operator.

    Example:
        GPIOD->MODER = 0x01;    // Set mode for a pin
        RCC->AHB1ENR |= ...;    // Enable clock for peripheral

------------------------------------------------------------------------------------------------------------------- */
#define GPIOD  ((GPIO_type *) GPIOD_BASE)       /* Pointer to GPIO_type struct at address GPIOD_BASE				*/
#define GPIOA  ((GPIO_type *) GPIOA_BASE)       /* Pointer to GPIO_type struct at address GPIOA_BASE				*/
#define RCC    ((RCC_type *) RCC_BASE)          /* Pointer to RCC_type struct at address RCC_BASE					*/
#define USART  ((USART_type *) USART_BASE)    	/* Pointer to USART_TypeDef struct at address USART_BASE			*/	


#endif