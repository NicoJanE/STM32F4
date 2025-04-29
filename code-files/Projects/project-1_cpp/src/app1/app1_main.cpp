/*  This file is part of: **STM32F4 Template Stack**_
     Copyright (c) 2025 Nico Jan Eelhart_
     This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
    
     Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
     https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_    */


#include "general.h"
#include "debug.h"
#include "./system/startup-code/registers.h"
#include "app1/app1_main.h"


int Application1::AppInitialize()
{
	return 0;
}


int Application1::Run()
{
		PRINT_DBG_PUBLIC();		 
		get_user_name();	
		return 0;
}