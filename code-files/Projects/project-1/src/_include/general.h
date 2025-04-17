/* 

This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_	  */


#ifndef GENERAL_H
#define GENERAL_H

/*  
==================================================================================================================
=   General description                                                                                          =
------------------------------------------------------------------------------------------------------------------ 
 
  PURPOSE
  - General project specific defintions
  - Standard C library includes that are used often.
      - Note for standard includes that are not used so often:    
          - Include those in the .c file OR
          - When used more often, but not so often, create a specialized  general-domain-name.h file instead of
            using this file.

------------------------------------------------------------------------------------------------------------------- */


/*   USAGE: Standard C Library includes */
#include <stdint.h>                     /* For type definitions; like  int8_t char  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#endif