#include "system/startup-code/base_app_factory.h"


/*  
==============================================================================================================
=   General Description                                                                                      =
--------------------------------------------------------------------------------------------------------------  

PURPOSE
    Polymorphic derived class of `base_app_factory`,implements the interface for a specific 
    applicationm: app1_factory.

    This module overrides the virtual functions declared in the base_app_factory_interface`.
    The methods in this class are typically called indirect (via vtable of base_app_factory) in main()
        
============================================================================================================== */


/* 	Derived struct.
    Implements the behavior of the abstract base interface: base_app_factory_interface.	*/	
struct app1_factory
{
	struct base_app_factory base;	
	int num;			
};


 /*
    Specific functions that override the base_app_factory_interface.
    These are called via the dispatch functions defined in the base.
-----------------------------------------------------------------------------------------------	*/

/*	Specific function: startup_app1 – overrides vtbl_startup in base_app_factory_interface 		*/
 int startup_app1(struct base_app_factory* basePtr);

 /*	Specific function: main_app1 – overrides vtbl_shutdown in base_app_factory_interface 		*/
 void main_app1(struct base_app_factory* basePtr);


/*	Factory function: app1_creator
    Allocates and initializes an app1_factory instance. Sets up the vtable for dynamic dispatch. */	
struct base_app_factory *app1_creator(void);
