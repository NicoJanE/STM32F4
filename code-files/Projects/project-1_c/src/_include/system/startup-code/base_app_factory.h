/* 

This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_		*/


#ifndef base_app_factory_H
#define  base_app_factory_H

/* -----------------------------------------------------------------------------------------------------------------
    Overview: Polymorphism in C

    This module implements runtime polymorphism using a virtual function table (vtable) design.

    The `base_app_factory_interface` defines a contract of function pointers. Each derived struct (e.g., `app1_factory`) 
    provides specific implementations of these functions and maps them to the vtable.

    Function calls are dispatched via a base pointer (`struct base_app_factory*`), allowing dynamic resolution at runtime:

        struct base_app_factory* init = app1_creator();
        int result = startup(init);   // Calls STM32F4-specific startup

    Key Concepts:
    - Virtual Function Table: Enables runtime selection of behavior via function pointers.
    - Dynamic Dispatch: Interface functions (e.g., `startup`, `main`) resolve to implementation-specific logic.
    - Factory Function: Each derived struct has a creation function that sets up the vtable.

    Benefits:
    - Modularity: New implementations can be added without modifying existing code.
    - Interface-based Design: Promotes separation of interface from implementation.
------------------------------------------------------------------------------------------------------------------- */


/*	Forward declaration: Abstract Base Struct		*/
struct base_app_factory;

/* 	Virtual function table (vtable) for base_app_factory	*/
struct base_app_factory_interface
{
	/*            
        Function pointers in the vtable that represent the interface operations.

        📍  The order of these function pointers is critical. It defines the layout
             used for dynamic dispatch. Always append new functions to the end to maintain 
             compatibility. */
             
	int (*vtbl_startup) (struct base_app_factory*);			
	void (*vtbl_main_app) (struct base_app_factory*);
};

/*	Abstract Base Struct containing the interface contract. 
	Implements the vtable to facilitate dynamic dispatch. */
struct base_app_factory
{	
	const struct base_app_factory_interface* const vtable;
};


/* 	
	Generic Dispatcher functions for the base_app_factory_interface.
    These functions serve as "generic aliases" that call the specific implementations for each instance.

    Typical usage:
        struct base_app_factory *init = app1_creator();
        int i = startup(init);      // Calls the specific startup_app1 implementation
 -------------------------------------------------------------------------------------------------------------------    */

/* 	Dispatch function: startup, calls the instance's specific startup function via the vtable */
static inline int startup(struct base_app_factory* instance)
{
	return  instance->vtable->vtbl_startup(instance);
}

/* 	Dispatch function: main, calls the instance's specific main function via the vtable */
static inline void main_app(struct base_app_factory* instance)
{
    instance->vtable->vtbl_main_app(instance);
}


#endif
