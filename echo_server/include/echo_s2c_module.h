#ifndef ECHO_S2C_MODULE_H
#define ECHO_S2C_MODULE_H

#include "stdint.h"
#include "unistd.h"
#include "s2c_server_api.h"



// Internal Server Context Management API
extern int Echo_Server_Basic_Update(serverContext_t* serverContextPtr, void*);
extern serverContext_t* Echo_Init_Server_Context(void*);
extern int Echo_Destroy_Server_Context(serverContext_t* serverContextPtr, void*);

typedef serverInterfaceBasic_t echoServerBasicInterface_t;
typedef serverContext_t echoServerContext_t;

// Define Global Function Tables for the Module
extern echoServerBasicInterface_t echo_server_basic_interface;
extern echoServerContext_t echo_server_context;

// Register the Global Function Tables for the Core Server Hypervisor
// Echo Server Module Registration Prototype
serverInterfaceBasic_t* register_server_interface(void);

#endif