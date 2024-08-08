#include <Onyx.h>
#include <Onyx/Platform/Platform.h>
#include <Onyx/Core/CVar.h>
#include <Onyx/Graphics/Window.h>
#include <cstdio>
#include <cstring>
#include <cstdio>

using namespace Onyx;

int main() {
    Onyx::Init();

#if ONYX_DEBUG
    Onyx::CVarManager::Get()->SetCVar_Bool("Onyx.Log.EnableForwarding", true);
#endif

    FILE* logFile = fopen("Log.txt", "a+");
    Onyx::Log::SetOutputStream(logFile);

    Onyx::Platform::Init();

    Onyx::Graphics::Window window("Hello!", 400, 200, 1280, 720);
    while (Onyx::Platform::PollEvents(window.GetHandle())) {
        static uint64_t frameIdx = 0;
        printf("\rFrame %d", frameIdx++);
        Onyx::Platform::Sleep(16);
    }


    printf("\n");
    window.Destroy();

    Onyx::Log::SetOutputStream(stdout);
    fclose(logFile);

    Onyx::Platform::Shutdown();

    return 0;
}