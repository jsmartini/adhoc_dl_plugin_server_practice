


#include "core_server.h"
#include <stdio.h>

coreServerContext_t* ctxPtr = NULL;

void Cleanup_Handler()
{
    Clean_Up_Core_Server_Context(ctxPtr);
}

void Print_Cli_Args(int argc, const char* argv[])
{
    printf("Args: ");
    for (int i = 0; i < argc; i++)
    {   
        printf("%s ", argv[i]);
    }
    printf("\n");
};  

int main(int argc, const char* argv[])
{
    printf("---- Core Server -----\n");
    Print_Cli_Args(argc, argv);
    printf("Initializing Core Server...");
    if(Initialize_Core_Server_Context(&ctxPtr) < 0)
    {
        printf(" Failed to Initialize, exiting\n");
        goto FAIL_EXIT;
    }
    printf(" Done\n");
    printf("core context pointer %p\n", ctxPtr);

    for (int i = 1; i < argc; i++)
    {
        printf("Registering Server Module %s...\n", argv[i]);
        if (Register_Server_Module(ctxPtr, argv[i]) < 0)
            goto FAIL_EXIT;
    }

    printf("Beginning Poll Loop...\n");
    while(Is_Core_Server_Alive(ctxPtr) == 1)
    {
        int update_status = Update_Core_Server_Context(ctxPtr);
        switch (update_status)
        {
            case -15:
                printf("No Services");
                goto FAIL_EXIT;
            default:
                continue;
        }
    }
        

    Cleanup_Handler();
    return 0;

    FAIL_EXIT:
        Cleanup_Handler();
        return -1;
}