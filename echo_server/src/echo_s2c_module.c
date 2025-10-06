
#include "echo_s2c_module.h"


serverInterfaceBasic_t* register_server_interface(void)
{
    return (serverInterfaceBasic_t*)&echo_server_basic_interface;
};