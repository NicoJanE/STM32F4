/* 

This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_	  */


 #include "system/c-implementation/syscalls.h"


//---------------------------------------------------------------------------------------------------------------------
// ✨ General Description   
//- -------------------------- 
//
// 💫 PURPOSE
//		Displays a message via the attached terminal and asks for your name via the same terminal.
//      
//		⚠️ NOTE: The `read` function is commented out by default to prevent the program from halting  (which would stop 
//			`main.c`  from running App2). Once you’ve confirmed that the terminal is working (e.g., with PuTTY), you can 
//			safely uncomment the line. 
//		  
//_____________________________________________________________________________________________________________________



class Application1
{
	public:

	Application1() = default;
	Application1(const Application1&) = delete;						// No copy
	Application1& operator = (const Application1&) = delete;		// No copy assignment	
	Application1(Application1&&) = delete;							// No move
	Application1& operator=(Application1&&) = delete;				// No Move assignment 
	~Application1() = default;

	//__________________________________________________#🟦🟦🟦#__________________________________________________


	int AppInitialize();

	int Run();
	
	//___________________________________________________#🟩🟩🟩#__________________________________________________


};


// 🟧🟧🟧 FREE Functions
// _____________________________________________________________________________________________________


inline void get_user_name(void) 
{
	char name[50];   
	int  len = 50;    
	
	printf("Enter your name <CR>: ");        // Use _read to get the input          
//	_read(0, name, len);                     // 0 refers to stdin (keyboard input)   ENABLE THIS TO READ FROM THE TERMINAL
	printf("\r\nYou gave me:, %s!", name);   // Print the name entered by the user  

}

//___________________________________________________#🟧🟧🟧#____________________________________________
