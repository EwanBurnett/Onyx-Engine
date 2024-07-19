#include <cstdio>
#include <Onyx.h>

#include <signal.h>

#if ONYX_PLATFORM_WINDOWS
const char* platformName = "Windows";
#elif ONYX_PLATFORM_LINUX
const char* platformName = "Linux";
#endif

void DebugBreak() {
#if ONYX_DEBUG
#if ONYX_PLATFORM_WINDOWS
    __debugbreak();
#elif ONYX_PLATFORM_LINUX
    raise(SIGTRAP);
#endif
#endif
}
int main() {
    printf("[%s]\tOnyx Version: %s\n", platformName, Onyx::GetVersionString().c_str());
    DebugBreak();

    return 0;
}