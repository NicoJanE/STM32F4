/* 

This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_	    */


#ifndef APP2_INITALIZE_H
#define APP2_INITALIZE_H

/*  
==============================================================================================================
=   General Description                                                                                      =
--------------------------------------------------------------------------------------------------------------  

PURPOSE
    -   calll by the `startup_app1` function. Initializes the registers specific for App2. 
        The generic register initialization is handled by the function `Reset_Handler(void)` in `startup.c`, 
        which also calls `main()`.

        This method is typically called from a derived member object of base_app_factory.
        
==============================================================================================================  */

static inline void initialize(void)     
{
    return;
}



#endif
