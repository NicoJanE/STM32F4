// This file is part of: **STM32F4 Template Stack**_
// Copyright (c) 2025 Nico Jan Eelhart_
// This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
// 
// Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
// https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_


// Owned includes
#include "main.h"
#include "cpp_entry.h"

/*
	!Carefull: To many breakpoints in the code will cause the debugger(gdb) to crash! with the error:
		" Error: A serious error occurred with gdb, unable to continue or interrupt We may not be able to 
		  recover from this point. You can try continuing or ending session. Must address root cause though"
		  6 breakpoints (perhaps 7) is the maximum I could set without crashing the debugger						*/
	
int main(void)
{	
	cpp_entry();    	
	return 0;
}