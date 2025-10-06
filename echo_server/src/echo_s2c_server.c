#include "echo_s2c_module.h"
#include "rb_queue.h"

// Internal Server Context Management API
int Echo_Server_Basic_Update(serverContext_t* serverContextPtr, void*)
{

};

serverContext_t* Echo_Init_Server_Context(void*)
{

};

int Echo_Destroy_Server_Context(serverContext_t* serverContextPtr, void*)
{

};

// Advanced Server Management
typedef struct 
{
    echoClient2ServerContext_t* ctx;
    char* message;
    size_t message_size;
} clientRequestEvent_t;

GEN_FIFO_QUEUE_TYPE(RequestEvent, 20, clientRequestEvent_t req;)

typedef struct
{
    int port;
    Rb_Fifo_Queue_RequestEvent request_queue;
} echoServerAdvancedContext_t;


typedef struct 
{
    echoServerAdvancedContext_t*(*Init_Echo_Server)();
    int(*Destroy_Echo_Server)();
    int(*Update_Echo_Server)(echoServerAdvancedContext_t* ctxPtr);

} Echo_Server_Advanced_Interface;


echoServerAdvancedContext_t* Echo_Server_Init_Advanced_Context()
{

};

int Echo_Server_Destroy_Advanced_Context(echoServerAdvancedContext_t* advCtxPtr)
{

};

// Server Module Bootstrap Interface Specification
echoServerBasicInterface_t echo_server_basic_interface = 
{
    .Basic_Update = &Echo_Client_Basic_Update,
    .Init_Server_Context = &Echo_Init_Server_Context,
    .Destroy_Server_Context = &Echo_Destroy_Server_Context,
    .Init_Adv_Context = NULL,
    .Init_Adv_Interface = NULL
};
