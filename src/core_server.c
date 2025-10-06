#include "core_server.h"
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
    handle = dlopen(server_module_pathname, RTLD_LAZY);
    errMsg = dlerror();
   // if (!errMsg || !*errMsg)
   // {
   //     err_code = -4;
   //     goto CLEANUP_EXIT;
   // }    

    register_server = dlsym(handle, "register_server_interface");
   // errMsg = dlerror();
   // if (!errMsg || !*errMsg)
   // {
   //     err_code = -5;
   //     goto CLEANUP_EXIT;
   // }    
    
    err_code= Add_Server_Context(register_server(),NULL, &coreCtxPtr->begin, &coreCtxPtr->end);
    if (err_code < 0)
    {
        goto CLEANUP_EXIT;
    }
    printf("Successfully Registered Module\n");
    return 0;

    CLEANUP_EXIT:
        printf("Failed on %d : %s\n", err_code, dlerror());

        return err_code;
};

int Initialize_Core_Server_Context(coreServerContext_t** coreCtxPtr)
{

    (*coreCtxPtr) = (coreServerContext_t*)malloc(sizeof(coreServerContext_t));
    if (*coreCtxPtr == NULL)
        return -1;
    printf("Allocated %lu @ %p for Core Server Context.\n", sizeof(coreServerContext_t), coreCtxPtr);
    (*coreCtxPtr)->alive = 1; // We are alive
    (*coreCtxPtr)->begin = NULL;
    (*coreCtxPtr)->end = NULL;
    printf("Allocated %lu @ %p for Core Server Context.\n", sizeof(coreServerContext_t), coreCtxPtr);
    return 0;
};

int Update_Core_Server_Context(coreServerContext_t* coreCtxPtr)
{
    serviceRegistryEntry_t* it = coreCtxPtr->begin;
    if (it == NULL)
        return -15;
    while (1)
    {
        printf("Hit %lu %p\n",it->hash, it);
        int update_status = (it->server_context->basic_interface->Basic_Update)(it->server_context, NULL);
        it = it->next_entry_ptr;
        if (it == NULL)
            break;
    }
    return 0;
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
    return 0;
};

