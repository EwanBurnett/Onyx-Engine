#ifndef ONYX_DEFAULTS_H
#define ONYX_DEFAULTS_H

#include "../Maths/Maths.h"

namespace Onyx {
    namespace Defaults {
        constexpr const char* WindowTitle = "Onyx-Application"; 
        const Maths::Vector2<uint32_t> WindowSize = { 600, 400 }; 
        const int MonitorIndex = 0; 
#if ONYX_PLATFORM_WINDOWS
        constexpr const char* PlatformName = "Windows"; 
#elif ONYX_PLATFORM_LINUX
        constexpr const char* PlatformName = "Linux"; 
#endif

        const uint8_t InvalidMemoryValue = 0xde;
        const uint8_t AllocatedMemoryValue = 0xff;
        const uint8_t FreedMemoryValue = 0xcc;

        const Maths::Vector2<uint32_t> Resolution = { 1920, 1080 }; 
        const uint16_t RefreshRate = 60; 
        const bool IsFullscreen = false; 
    }
}

#endif