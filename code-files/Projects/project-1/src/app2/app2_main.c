/*  This file is part of: **STM32F4 Template Stack**_
     Copyright (c) 2025 Nico Jan Eelhart_
     This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
    
     Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
     https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_    */


// Std includes
#include <stdlib.h>
#include <string.h>

#include "general.h"
#include "app2/app2_main.h"
#include "system/c-implementation/syscalls.h"


void get_user_name(void) {
    char name[50];   
    int  len = 50;    
    
	printf("Enter your name <CR>: ");        /* Use _read to get the input          */
    _read(0, name, len);                     /* 0 refers to stdin (keyboard input)  */
    printf("\r\nYou gave me:, %s!", name);   /* Print the name entered by the user  */

}


int app2_main(void)
{
    USART2_Init();                          
    Clear();                                
	
	char *test = (char *)malloc(100);
    strcpy(test,"Hello worls!!\0");
	printf("\r\n value:%s",test);

	puts("\r\n\t\t Let try some input\n"); 	
	free(test);
	
	get_user_name();

    return 0;

}