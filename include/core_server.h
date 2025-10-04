#ifndef CORE_SERVER_H
#define CORE_SERVER_H

#include "service_registry.h"

#include "time.h"
#include "unistd.h"

typedef struct 
{
    int alive;
    struct timespec server_start_time;

    serviceRegistryEntry_t* begin;
    serviceRegistryEntry_t* end;

} coreServerContext_t;

int Is_Core_Server_Alive(coreServerContext_t* coreCtxPtr);
int Register_Server_Module(coreServerContext_t* coreCtxPtr, const char* server_module_pathname);
int Initialize_Core_Server(coreServerContext_t* coreCtxPtr);
int Update_Core_Server_Context(coreServerContext_t* coreCtxPtr);
int Clean_Up_Core_Server_Context(coreServerContext_t* coreCtxPtr);

#endif