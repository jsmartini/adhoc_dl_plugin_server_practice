#ifndef CLIENT_S2C_API_H
#define CLIENT_S2C_API_H

#include "unistd.h"

typedef struct client2ServerContext_t client2ServerContext_t;
typedef struct
{
    uint16_t protocol_version;
    uint16_t service_class;
    
    // The generic poll function
    int (*Basic_Update)(client2ServerContext_t* clientContextPtr, void* payloadPtr);
    // The generic initialization function
    void* (*Init_Adv_Interface)(void);
    void* (*Init_Adv_Context)(void);

    // Initializer
    client2ServerContext_t* (*Init_Client2Server_Context)(void*);
    // Destructor
    int (*Destroy_Client2Server_Context)(void*);
} client2ServerBasicInterface_t;

typedef struct client2ServerContext_t
{
    client2ServerBasicInterface_t* basic_interface_ptr;
    void* adv_interface_ptr;
    void* adv_context;
} client2ServerContext_t;



#endif