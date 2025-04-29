/* 
This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each 
file, and refer to: https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_	  */


#ifndef DEBUG_H
    #define DEBUG_H

    //---------------------------------------------------------------------------------------------------------------------
    // ✨ General Description   
    //- -------------------------- 
    //
    // 💫 PURPOSE
    //      Debug with style!
    //        - The print fuunction will print the function, and the color indicates if it private or public
    //
    //            
    //_____________________________________________________________________________________________________________________

    #define COL_BLUE    "\033[0;36m"
    #define COL_RESET   "\033[0m"
    #define COL_LGREEN  "\033[1;32m"
    #define COL_RED     "\033[1;31m"
    #define PRINT_DBG_PUBLIC()  \
        printf("\r\nIn:%s  %s%s(🟩)\r\n%s", COL_BLUE, __PRETTY_FUNCTION__, COL_LGREEN, COL_RESET)
    #define PRINT_DBG_PRIVATE() \
        printf("\r\nIn:%s  %s%s(🟥)\r\n%s", COL_BLUE, __PRETTY_FUNCTION__, COL_RED, COL_RESET)

        
#endif