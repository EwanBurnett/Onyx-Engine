#ifndef ONYX_DEFAULTS_H
#define ONYX_DEFAULTS_H

#include "../Maths/Maths.h"

namespace Onyx {
    namespace Defaults {
        inline const char* WindowTitle = "Onyx-Application"; 
        inline const Maths::Vector2<uint32_t> WindowSize = { 600, 400 }; 
        inline const int MonitorIndex = 0; 
#if ONYX_PLATFORM_WINDOWS
        inline const char* PlatformName = "Windows"; 
#elif ONYX_PLATFORM_LINUX
        inline const char* PlatformName = "Linux"; 
#endif

        inline const uint8_t InvalidMemoryValue = 0xde;
        inline const uint8_t AllocatedMemoryValue = 0xff;
        inline const uint8_t FreedMemoryValue = 0xcc;

        inline const Maths::Vector2<uint32_t> Resolution = { 1920, 1080 }; 
        inline const uint16_t RefreshRate = 60; 
        inline const bool IsFullscreen = false; 
    }
}

#endif