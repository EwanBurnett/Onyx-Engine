#include <Onyx.h>
#include <Onyx/Platform/Platform.h>
#include <Onyx/Core/CVar.h>
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

    Onyx::WindowHandle hwnd = Onyx::Platform::CreateWindow();

    Onyx::Platform::SetWindowPosition(hwnd, 300, 100);
    Onyx::Platform::SetWindowTitle(hwnd, "Testing!");
    Onyx::Platform::SetWindowSize(hwnd, 500, 400);

    while (Onyx::Platform::PollEvents(hwnd)) {
        static uint64_t frameIdx = 0;
        printf("\rFrame %d", frameIdx++);
        Onyx::Platform::Sleep(16);
    }

    Onyx::Platform::DestroyWindow(hwnd);

    printf("\n");

    Onyx::Log::SetOutputStream(stdout);
    fclose(logFile);

    Onyx::Platform::Shutdown();

    return 0;
}