#include "helper.h"
#include "s2c_server_api.h"
#include "service_registry.h"
#include "malloc.h"

int Get_Server_Context(serverContext_t* targetCtxPtr, uint32_t serviceHash, serviceRegistryEntry_t* begin)
{
    serviceRegistryEntry_t* it = begin;
    while (it != NULL)
    {
        if (serviceHash == Get_Service_Hash(
            it->server_context->basic_interface->protocol_version, 
            it->server_context->basic_interface->service_class))
        {
            targetCtxPtr = it->server_context;
            return 0;
        }
        it = it->next_entry_ptr;
    }
    return -1;
};

int Add_Server_Context(serverInterfaceBasic_t* ibPtr, void* initPayloadPtr, serviceRegistryEntry_t** beginPtr, serviceRegistryEntry_t** endPtr)
{
    if (*endPtr != NULL)
    {
        serviceRegistryEntry_t* end = *endPtr;
        end->next_entry_ptr = (serviceRegistryEntry_t*)malloc(sizeof(serviceRegistryEntry_t));
        end->next_entry_ptr->server_context = (*ibPtr->Init_Server_Context)(initPayloadPtr);
        end->next_entry_ptr->hash = Get_Service_Hash(ibPtr->protocol_version, ibPtr->service_class);
        end->next_entry_ptr->next_entry_ptr = NULL;
        *endPtr = end->next_entry_ptr;
        return 0;
    }

    if (*beginPtr == NULL)
    {
        serviceRegistryEntry_t* first = (serviceRegistryEntry_t*)malloc(sizeof(serviceRegistryEntry_t));
        first->server_context = (*ibPtr->Init_Server_Context)(initPayloadPtr);
        first->hash = Get_Service_Hash(ibPtr->protocol_version, ibPtr->service_class);
        first->next_entry_ptr = NULL;
        *beginPtr = first;
        *endPtr = first;
        return 0;
    }

    return -1;
};

int Destroy_Server_Registry(serviceRegistryEntry_t* begin, serviceRegistryEntry_t* end)
{
    serviceRegistryEntry_t* it = begin;
    while(it->next_entry_ptr != NULL)
    {
        serviceRegistryEntry_t* curr = it;
        it = it->next_entry_ptr;
        (*curr->server_context->basic_interface->Destroy_Server_Context)(curr->server_context, NULL);
        free(curr->server_context);
    }
    return 0;
};

