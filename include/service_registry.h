#ifndef SERVICE_REGISTRY_H
#define SERVICE_REGISTRY_H

#include "unistd.h"
#include "stdint.h"
#include "api/s2c_server_api.h"

typedef struct serviceRegistryEntry_t serviceRegistryEntry_t;
typedef struct serviceRegistryEntry_t
{
    uint32_t hash;
    // Singleton Context
    serverContext_t* server_context;

    serviceRegistryEntry_t* next_entry_ptr;

} serviceRegistryEntry_t;

int Get_Server_Context(serverContext_t* targetCtxPtr, uint32_t serviceHash, serviceRegistryEntry_t* begin);
int Add_Server_Context(serverInterfaceBasic_t* ibPtr, void* initPayloadPtr, serviceRegistryEntry_t** begin, serviceRegistryEntry_t** end);
int Destroy_Server_Registry(serviceRegistryEntry_t* begin, serviceRegistryEntry_t* end);

#endif