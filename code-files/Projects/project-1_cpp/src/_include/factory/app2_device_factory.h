#ifndef APP2_DEVICE_FACTORY
#define APP2_DEVICE_FACTORY

/* 
This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each
file, and refer to:https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_	                                */

#include "general.h"
#include "debug.h"
#include "factory/base_device_factory.h"
#include "system/c-implementation/syscalls.h"

#include "app2/app2_main.h"


// Remark:  Some of you will find the symbols and documentation a bit much and will ask your self is that really need?
//          Eh... Yes 😃. It gives a bit extra quick overview and is a bit more inviting to read I hope. But in the end 
//          of course personal, so use it or 'Go Your Own Way'🎵
//
//      #🟦🟦🟦#    End constructors/destructor
//      #🟩🟩🟩#    End Public methods
//      #🟥🟥🟥#    End private methods
//      #🟧🟧🟧#    End Free functions
//      #⚡⚡⚡#    End virtual functions
//
//      💫           Virtual
//

                    
//---------------------------------------------------------------------------------------------------------------------
// ✨ General Description   
//- -------------------------- 
//
// 💫 PURPOSE
//    Polymorphic derived class of `BaseDeviceFactory`,implements the interface for a specific device, in order to:
//        - Initialization the specific device
//        - to dispatch to the main application
//
//    This module overrides the virtual functions declared in the BaseDeviceFactory`.
//            
//_____________________________________________________________________________________________________________________



class App2DeviceFactory : public BaseDeviceFactory 
{
public:
    
    App2DeviceFactory() {}
    
    //__________________________________________________#🟦🟦🟦#__________________________________________________


    // The main entry point for App1
    inline void AppDispatcher() override 
    {
        PRINT_DBG_PUBLIC();
        printf("This will run blinky! Your leds on the device\r\n");
        
        Application2 app;
        auto nRet=  app.Run();
    }

    //___________________________________________________#🟩🟩🟩#__________________________________________________


    private:
    
    inline int Initialize() 
    {        
        USART2_Init();          // Make sure we can write to the COM port on the device
        // Clear();

        PRINT_DBG_PRIVATE();
        printf("- Use this for specific initilization of your device(MCU)\r\n");
        return 0;
    }

    //___________________________________________________#🟥🟥🟥#__________________________________________________
};
 
#endif // APP2_DEVICE_FACTORY