/* 

This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_	  */


#ifndef APP1_INITALIZE_H
#define APP1_INITALIZE_H

#include "system/startup-code/registers.h"

/*  
==============================================================================================================
=   General Description                                                                                      =
--------------------------------------------------------------------------------------------------------------  

PURPOSE
    -   calll by the `startup_app1` function. Initializes the registers specific for App1. 
        The generic register initialization is handled by the function `Reset_Handler(void)` in `startup.c`, 
        which also calls `main()`.

        This method is typically called from a derived member object of base_app_factory.
        
==============================================================================================================  */

static inline void initialize(void)
{
    // Manually clear USART2 registers (if garbage is present)
    USART->SR = 0;  // Clear status register
    USART->DR = 0;  // Clear data register

    /* Reset the RCC clock configuration to the default reset state */
    /* Set HSION bit */
    RCC->CR |= (1 << 0);

    /* Reset CFGR register */
    RCC->CFGR = 0x00000000;

    /* Reset HSEON (16), CSSON (19) and PLLON (24) bits */
    RCC->CR &= ~(uint32_t)((1 << 16) | (1 << 19) | (1 << 24));

    /* Reset PLLCFGR register to reset value */
    RCC->PLLCFGR = 0x24003010;

    /* Reset HSEBYP bit */
    RCC->CR &= ~(uint32_t)(1 << 18);

    // The processor is now running from the HSI clock which is the internal
    //   high speed clock

    /* Disable all RCC interrupts */
    RCC->CIR = 0x00000000;
    return;
}



#endif
