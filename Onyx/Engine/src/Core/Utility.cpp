#include "Onyx/Core/Utility.h"

#if ONYX_PLATFORM_LINUX
#include <signal.h>
#endif

void Onyx::DebugBreak() {
#if ONYX_DEBUG
#if ONYX_PLATFORM_WINDOWS
    __debugbreak();
#elif ONYX_PLATFORM_LINUX
    raise(SIGTRAP);
#endif
#endif
}
