
#ifndef BASE_DEVICE_FACTORY_H
#define BASE_DEVICE_FACTORY_H

/* 
This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each
file, and refer to:https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_	                                */


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


class BaseDeviceFactory 
{
public:
    
    virtual void AppDispatcher() = 0;           // 💫 Pure virtual function for AppDispatcher
    virtual ~BaseDeviceFactory() = default;     // 💫 Virtual destructor
            
};

#endif // BASE_DEVICE_FACTORY_H
