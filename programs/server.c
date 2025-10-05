


#include "core_server.h"
#include <stdio.h>

coreServerContext_t* ctx_ptr = NULL;

void Cleanup_Handler()
{
    Clean_Up_Core_Server_Context(ctx_ptr);
}

void Print_Cli_Args(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++)
    {   
        printf("%s ", argv[i]);
    }
    printf("\n");
};  

int main(int argc, char* argv[])
{
    Print_Cli_Args(argc, argv);
    printf("---- Core Server -----\n");
    printf("Initializing Core Server...");
    if(Initialize_Core_Server_Context(&ctx_ptr) < 0)
    {
        printf(" Failed to Initialize, exiting\n");
        goto FAIL_EXIT;
    }
    printf(" Done\n");
    printf("core context pointer %p\n", ctx_ptr);

    for (int i = 1; i < argc; i++)
    {
        printf("Registering Server Module %s...", argv[i]);
        if (Register_Server_Module(ctx_ptr, argv[i]) < 0)
            goto FAIL_EXIT;
        printf(" Done\n");
    }

    printf("Beginning Poll Loop...\n");
    while(Is_Core_Server_Alive(ctx_ptr) == 1)
        Update_Core_Server_Context(ctx_ptr);

    Cleanup_Handler();
    return 0;

    FAIL_EXIT:
        Cleanup_Handler();
        return -1;
}