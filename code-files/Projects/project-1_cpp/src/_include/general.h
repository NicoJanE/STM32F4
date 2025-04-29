/* 

This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each 
file, and refer to: https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_	  */


#ifndef GENERAL_H
  #define GENERAL_H

  /*  
  ==================================================================================================================
  =   General description                                                                                          =
  ------------------------------------------------------------------------------------------------------------------ 
  
    PURPOSE
    - General project-specific definitions
    - Standard C library includes that are used often.
        - Note for standard includes that are not used so often:    
            - Include those in the .c file OR
            - When used more often, but not so often, create a specialized general-domain-name.h file instead of
              using this file.

  LINK GUARDS
  - We use linkage guards in a single `general.h` include file to ensure proper C linkage when called from C++.
    This allows functions and headers to be compatible with both C and C++ codebases.

    ALTERNATIVE APPROACH:
    1. In larger projects or when there is a clear separation between C and C++ components, consider splitting this
       header into two separate headers:
       - `general_c.h` for C-specific includes
       - `general_cpp.h` for C++-specific includes
       This approach is useful when:
       - The headers required for C and C++ diverge significantly.
       - You want to keep the headers lightweight and modular.

    2. You could use the special `<cstring>` headers (not by default included in the include path) to use functions
       with C linkage in C++. However, this does NOT work in our case because there are a lot of dependencies.

    📌 For this project, we use a single `general.h` file for simplicity and ease of maintenance.

  ------------------------------------------------------------------------------------------------------------------- */


  //  USAGE: Standard C Library includes
  

  // Use <string.h> with C linkage guards for compatibility
  #ifdef __cplusplus
    extern "C" 
    {
    #endif
      
      #include <string.h>
      #include <stdint.h>                         // For type definitions; like int8_t, char 
      #include <stdio.h>
      #include <stdlib.h>

      // NOT SURE to centralize this. perhaps better to include where needed??
     // include "system/c-implementation/syscalls.h"

    #ifdef __cplusplus
    }
  #endif

#endif