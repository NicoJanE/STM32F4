/* 

This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_		*/

#include "system/c-implementation/syscalls.h"


//---------------------------------------------------------------------------------------------------------------------
// ✨ General Description   
//- -------------------------- 
//
// 💫 PURPOSE
//		Blinky, blinks the leds on the device.
//         
//_____________________________________________________________________________________________________________________


class Application2
{
	public:

	Application2() = default;
	Application2(const Application2&) = delete;						// No copy
	Application2& operator = (const Application2&) = delete;		// No copy assignment	
	Application2(Application2&&) = delete;							// No move
	Application2& operator=(Application2&&) = delete;				// No Move assignment 
	~Application2() = default;

	//__________________________________________________#🟦🟦🟦#__________________________________________________


	int AppInitialize();

	int Run();
	
	//___________________________________________________#🟩🟩🟩#__________________________________________________

};


// 🟧🟧🟧 FREE Function
// _____________________________________________________________________________________________________

// A simple and not accurate delay function
static inline void delay(volatile uint32_t s)
{
	for(; s>0; s--)
    {
		// Do nothing
	}
}

//___________________________________________________#🟧🟧🟧#____________________________________________
