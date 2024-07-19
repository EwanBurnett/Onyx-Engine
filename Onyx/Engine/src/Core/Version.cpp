/**
* @file Version.cpp
* @warning THIS FILE IS GENERATED BY CMAKE
* @warning DO NOT MODIFY
*/

#include "Onyx/Core/Version.h"
#include <cstdio>

namespace Onyx{
    const int ONYX_GIT_HASH = 0x6c4ec32;
    const int ONYX_VERSION_MAJOR = 0;
    const int ONYX_VERSION_MINOR = 0;
    const int ONYX_VERSION_ISSUE = 1;
}

std::string Onyx::GetVersionString(){
    char buffer[0xff]; 
    sprintf(buffer, "v%d.%d.%d Hash[0x%x]", ONYX_VERSION_MAJOR, ONYX_VERSION_MINOR, ONYX_VERSION_ISSUE, ONYX_GIT_HASH);

    return buffer; 
}
