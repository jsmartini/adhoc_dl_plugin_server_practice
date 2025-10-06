
#include "echo_s2c_module.h"
#include "stdio.h"

serverInterfaceBasic_t* register_server_interface(void)
{
    printf(":: Loading Echo Server\n");
    return (serverInterfaceBasic_t*)&echo_server_basic_interface;
};