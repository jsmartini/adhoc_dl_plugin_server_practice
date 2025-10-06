#ifndef SERVER_S2C_API_H
#define SERVER_S2C_API_H
#include "stdint.h"
#include "unistd.h"

typedef struct serverContext_t serverContext_t;

typedef struct
{
    uint16_t protocol_version;
    uint16_t service_class;
    
    // First Stage Update
    int (*Basic_Update)(serverContext_t*,void*);
    
    // Initializer
    serverContext_t* (*Init_Server_Context)(void*);
    // Destructor
    int (*Destroy_Server_Context)(serverContext_t* ctxPtr, void*);
} serverInterfaceBasic_t;

typedef struct serverContext_t
{
    void* instance_ptr;
    serverInterfaceBasic_t* basic_interface;
} serverContext_t;



#endif