#ifndef ONYX_CORE_TYPES_H
#define ONYX_CORE_TYPES_H
/**
* @file Types.h
*
* ------------------------------------------
* @author Ewan Burnett (EwanBurnettSK@outlook.com)
* @date 2024/08/08
*/
#include <cstdint> 
#include "../Maths/Vector2.h"
#include "Defaults.h"

namespace Onyx {

    typedef uint64_t WindowHandle;

    struct VideoMode {
        Maths::Vector2<uint32_t> resolution = Defaults::Resolution; 
        uint16_t refreshRate = Defaults::RefreshRate; 
        bool isFullscreen = Defaults::IsFullscreen; 
    };

}

#endif