

#include "cpp_entry.h"
#include "general.h"

#include "factory/base_device_factory.h"
#include "factory/app1_device_factory.h"
#include "factory/app2_device_factory.h"


// Called from the main.c file. Here we enter the C++ world, in essence this is the C++ main file
// from where we dispacth to a specific application via a bas_device_factory
int cpp_entry(void) 
{    
    BaseDeviceFactory* factory_1 = new App1DeviceFactory(true); 
    BaseDeviceFactory* factory_2 = new App2DeviceFactory(); 
    
    factory_1->AppDispatcher();
    factory_2->AppDispatcher();
 

    return 0;
}

