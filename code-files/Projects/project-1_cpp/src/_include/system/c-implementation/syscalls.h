/* 

This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_	  */


#ifndef SYSCALLS_H
#define SYSCALLS_H

/*  
==============================================================================================================
=   General description                                                                                      =
--------------------------------------------------------------------------------------------------------------  
 
PURPOSE
  - Header file for implementing the required (interface) functions for printf, scanf, putc, ect.
  - This implementation uses Newlib, so the functions likely depend on it, but may also be adaptable for use with 
    other C libraries
  - Function definitions
  - Also contains definitions from the linker script that are required
  
-------------------------------------------------------------------------------------------------------------- */

#ifndef S_IFCHR
#define S_IFCHR 0020000         /*  Character device indicator (if not already defined) */
#endif

#ifdef __cplusplus
extern "C" {
#endif

  void        USART2_Init(void);         
  void        SystemClock_Config(void); 
  int         _read(int file, char *ptr, int len) ; 
  int         _write(int file, char *ptr, int len); 
  void        Clear(void);


  
  /* -------------------------------------------------------------------------------------------------
   =  C++ system functions to allow usage of operator new and delete in embedded environments.  
       These stubs prevent linker errors such as: 'undefined reference to __dso_handle'.

      Explanation:
      - Operator new uses malloc() internally.
      - malloc() ultimately relies on _sbrk(), which must be provided separately (see syscalls.c).
      - __dso_handle, __cxa_atexit, and __cxa_finalize are part of the minimal C++ runtime support.

   ---------------------------------------------------------------------------------------------------- */
  int __cxa_atexit(void (*func)(void*), void *arg, void *dso) ;
  void __cxa_finalize(void *dso) ;



#ifdef __cplusplus
}
#endif

/* Defined in linker script */
extern char _end;               /* Defined at end of .bss in the linker script  */
extern char __StackTop;         /* Defined in linker script, top of RAM         */
static char *heap_end = &_end;  /* Heap starts at _end (end of .bss), used by _sbrk() for dynamic memory allocation       */

#endif