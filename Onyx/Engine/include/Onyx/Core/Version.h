#ifndef ONYX_VERSION_H
#define ONYX_VERSION_H
/**
* @file Version.h
* @brief Contains the Engine's Version Information. 
* @details Versions are formatted as v[MAJOR].[MINOR].[ISSUE][GIT HASH]
* @details e.g.v0.1.2[ff1c8a]
*
* ------------------------------------------
* @author Ewan Burnett(EwanBurnettSK@Outlook.com)
* @date 2024 - 07 - 19
*/ 

#include <string> 

namespace Onyx
{
    /**
     * @brief Returns a formatted version string
     * @return The current Engine Version, formatted as v[MAJOR].[MINOR].[ISSUE][GIT HASH].
    */
    std::string GetVersionString();

    extern const int ONYX_VERSION_MAJOR;    //v[MAJOR].x.x [xxxx]
    extern const int ONYX_VERSION_MINOR;    //vx.[MINOR].x [xxxx]
    extern const int ONYX_VERSION_ISSUE;    //vx.x.[ISSUE] [xxxx]
    extern const int ONYX_GIT_HASH;         //vx.x.x [HASH]
}

#endif