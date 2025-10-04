#ifndef HELPER_H
#define HELPER_H

#include "stdint.h"

uint32_t Get_Service_Hash(uint16_t protocol_version, uint16_t service_class);
uint16_t Get_Service_Protocol_Version(uint32_t Service_Hash);
uint16_t Get_Service_Class(uint32_t Get_Service_Hash);


#endif