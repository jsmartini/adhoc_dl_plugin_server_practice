#include "helper.h"


uint32_t Get_Service_Hash(uint16_t protocolVersion, uint16_t serviceClass)
{
    uint32_t hash = (protocolVersion << 16) | (serviceClass);
    return hash;
};

uint16_t Get_Service_Protocol_Version(uint32_t serviceHash)
{
    uint16_t serviceProtocolVersion = (uint16_t)(serviceHash >> 16); 
    return serviceProtocolVersion;
};

uint16_t Get_Service_Class(uint32_t serviceHash)
{
    uint16_t serviceClass = (uint16_t)(0x0000FFFF & serviceHash);
    return serviceClass;
};