#ifndef ONYX_VERSION_H
#define ONYX_VERSION_H
#include <string> 

namespace Onyx
{
    std::string GetVersionString();

    extern const int ONYX_VERSION_MAJOR;
    extern const int ONYX_VERSION_MINOR;
    extern const int ONYX_VERSION_ISSUE;
    extern const int ONYX_GIT_HASH;
}

#endif