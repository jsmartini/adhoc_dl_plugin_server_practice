#ifndef SERVER_S2C_API_H
#define SERVER_S2C_API_H

#include "unistd.h"
#include "s2c_client_api.h"

typedef struct serverContext_t serverContext_t;

typedef struct
{
    uint16_t protocol_version;
    uint16_t service_class;
    
    // First Stage Update
    int (*Basic_Update)(serverContext_t*,void*);
    
    void* (*Init_Adv_Interface)(void);
    void* (*Init_Adv_Context)(void);

    // Initializer
    serverContext_t* (*Init_Server_Context)(void*);
    // Destructor
    int (*Destroy_Server_Context)(serverContext_t* ctxPtr, void*);
} serverInterfaceBasic_t;

typedef struct serverContext_t
{
    client2ServerBasicInterface_t* basic_client_interface;
    serverInterfaceBasic_t* basic_interface;
    void* adv_context;
    void* adv_interface;
} serverContext_t;



#endif