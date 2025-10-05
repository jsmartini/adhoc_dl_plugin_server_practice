#include "core_server.h"
#include "s2c_client_api.h"
#include "s2c_server_api.h"

#include "time.h"
#include "unistd.h"
#include "malloc.h"
#include "dlfcn.h"
#include "stdio.h"

int Is_Core_Server_Alive(coreServerContext_t* coreCtxPtr)
{
    if (coreCtxPtr == NULL)
    {
        printf("Got Null Pointer, failing...\n");
        return -13;
    }
    return coreCtxPtr->alive;
};

int Register_Server_Module(coreServerContext_t* coreCtxPtr, const char* server_module_pathname)
{
    int err_code = 0;
    const char* errMsg;
    void* handle;

    serverInterfaceBasic_t*(*register_server)(void);

    if (!server_module_pathname || !*server_module_pathname)
        return -1;

    if(access(server_module_pathname, F_OK) != 0)
    {
        printf("Server Module %s does not exist.. failing\n", server_module_pathname);
        return -2;
    }
        

    dlerror();
    handle = dlopen(server_module_pathname, RTLD_NOW | RTLD_LOCAL);
    errMsg = dlerror();
    if (!errMsg || !*errMsg)
    {
        err_code = -2;
        goto CLEANUP_EXIT;
    }    

    register_server = dlsym(handle, "register_server_interface");
    errMsg = dlerror();
    if (!errMsg || !*errMsg)
    {
        err_code = -3;
        goto CLEANUP_EXIT;
    }    
    
    Add_Server_Context(register_server(),NULL, &coreCtxPtr->begin, &coreCtxPtr->end);
    goto CLEANUP_EXIT;

    CLEANUP_EXIT:
        dlclose(handle);
        return err_code;
};

int Initialize_Core_Server_Context(coreServerContext_t** coreCtxPtr)
{

    (*coreCtxPtr) = (coreServerContext_t*)malloc(sizeof(coreServerContext_t));
    if (*coreCtxPtr == NULL)
        return -1;
    printf("Allocated %u @ %p for Core Server Context.\n", sizeof(coreServerContext_t), coreCtxPtr);
    (*coreCtxPtr)->alive = 1; // We are alive
    (*coreCtxPtr)->begin = NULL;
    (*coreCtxPtr)->end = NULL;
    printf("Allocated %u @ %p for Core Server Context.\n", sizeof(coreServerContext_t), coreCtxPtr);
    return 0;
};

int Update_Core_Server_Context(coreServerContext_t* coreCtxPtr)
{
    serviceRegistryEntry_t* it = coreCtxPtr->begin;
    if (it == NULL)
        return 1;
    while (it->next_entry_ptr != NULL)
    {
        (*it->server_context->basic_interface->Basic_Update)(it->server_context, NULL);
        it = it->next_entry_ptr;
    }
};

int Clean_Up_Core_Server_Context(coreServerContext_t* coreCtxPtr)
{
    if (coreCtxPtr == NULL)
    {
        printf("Null context pointer\n");
        return -13;
    }
    coreCtxPtr->alive = 0;
    Destroy_Server_Registry(coreCtxPtr->begin, coreCtxPtr->end);
    free(coreCtxPtr);
};

