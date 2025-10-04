


#include "core_server.h"

static coreServerContext_t* ctx_ptr = NULL;


void Cleanup_Handler()
{
    Clean_Up_Core_Server_Context(ctx_ptr);
}

int main(int argc, char* argv[])
{
    Initialize_Core_Server(ctx_ptr);

    for (int i = 1; i < argc; i++)
    {
        if (Register_Server_Module(ctx_ptr, argv[i]) < 0)
            goto FAIL_EXIT;
    }

    while(Is_Core_Server_Alive(ctx_ptr))
        Update_Core_Server_Context(ctx_ptr);

    Cleanup_Handler();
    return 0;

    FAIL_EXIT:
        Cleanup_Handler();
        return -1;
}