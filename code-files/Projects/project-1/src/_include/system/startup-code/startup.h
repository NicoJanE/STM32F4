/* 

This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_	    */


#ifndef STARTUP_H
#define STARTUP_H

/*  
==============================================================================================================
=   General Description                                                                                      =
--------------------------------------------------------------------------------------------------------------  

PURPOSE
    - Startup header file for the STM32F4-Discovery board. It declares:
        - Vector interrupt definitions (see details in the corresponding C file)
        - The Reset_Handler() function, which is referenced in the vector table and executed on device reset
        - The _init_data() function, called by Reset_Handler(), to copy initialized data from ROM to RAM
        - A Default_Handler() function, which does nothing and is assigned to unimplemented interrupts
        - A reference to __StackTop, defined in the linker script and used as the first entry in the vector table

    NOTE:
        - The __StackTop address and the first 15 entries in the vector table are defined by the ARM Cortex-M architecture
        - The remaining interrupt vector entries are vendor-specific (defined by STMicroelectronics in this case)

==============================================================================================================  */


/* Ensures the linker can find main(). This declaration is required. */
extern int main(void);

/* 
    Although not strictly necessary (since main() is directly referenced by Reset_Handler()), 
    it's good practice to mark it as used to prevent compiler optimization from removing it.    */
__attribute__((used)) int main(void);	
										
/* __StackTop is defined in the linker script; it should point to the top of the stack */
extern unsigned long __StackTop;


/*  Function declarations	*/
void Reset_Handler(void);
void _init_data(void);
void Default_Handler(void);


#endif
