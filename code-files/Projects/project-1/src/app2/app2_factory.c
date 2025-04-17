/*  This file is part of: **STM32F4 Template Stack**_
     Copyright (c) 2025 Nico Jan Eelhart_
     This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
    
     Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
     https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_    */


#include "general.h"

#include "system/startup-code/base_app_factory.h"
#include "app2/app2_factory.h"
#include "app2/app2_initialize.h"
#include "app2/app2_main.h"



/* Specific implementation of the interface pointer function: start_up	*/
int startup_app2(struct base_app_factory* basePtr)
{
	struct app2_factory *implementation =(void*)basePtr;
	initialize();			/* Execute the 'private' initialization (static inline) for application app2 */
	
	implementation->num = 2100;
	return implementation->num;

}
/* Specific implementation of the interface pointer function: shut_down */
void main_app2(struct base_app_factory* basePtr)
{
	struct app2_factory *implementation =(void*)basePtr;
	implementation->num = 100;
	app2_main();			/* Execute the main for application app1	*/

}

/* 	Factory function for app2_factory
	Initializes an instance and maps its functions to the vtable	*/
struct base_app_factory *app2_creator(void)
{
	/* ⚠️ 	General: Do not use static for instances that hold mutable or instance-specific state — it causes shared state between "instances".
			General Static(more efficient) base instance, copied into dynamically allocated structures	*/

	static const struct base_app_factory_interface vtable = {startup_app2, main_app2};	/* 	Define the specific interface members.	 	*/
	static struct base_app_factory base = {&vtable};									/* 	Assign them to base (temp object).			*/
	struct app2_factory *app2_factory = malloc(sizeof(*app2_factory));					/* 	Allocate memory for the derived structure.	*/
	memcpy(&app2_factory->base, &base, sizeof(base));									/* 	Copy the base with the specific interface. 
																							implementation to the derived structure.	*/
	app2_factory->num =99;
	return &app2_factory->base;
}
