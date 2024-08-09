#include <Onyx.h>
#include <Onyx/Platform/Platform.h>
#include <Onyx/Core/CVar.h>
#include <Onyx/Graphics/Window.h>
#include <cstdio>
#include <cstring>
#include <cstdio>
#include <Onyx/Core/String.h>

using namespace Onyx;

int main() {
    Onyx::Init();

#if ONYX_DEBUG
    Onyx::CVarManager::Get()->SetCVar_Bool("Onyx.Log.EnableForwarding", true);
#endif

    FILE* logFile = fopen("Log.txt", "a+");
    Onyx::Log::SetOutputStream(logFile);

    Onyx::Platform::Init();

    Onyx::String title;
    title.Format("Testbed - Onyx %s", Onyx::GetVersionString().c_str());

    Onyx::Graphics::Window window(title.c_str(), 400, 200, 1280, 720);
    auto h = window.GetHandle();
    Onyx::Platform::SetWindowIcon(h, "../../../../Resources/Onyx_Icon_256x256.ico");

    while (Onyx::Platform::PollEvents(window.GetHandle())) {
        static uint64_t frameIdx = 0;
        printf("\rFrame %d", frameIdx++);
        title.Format("Frame %d    Testbed - Onyx %s", frameIdx++, Onyx::GetVersionString().c_str());
        Onyx::Platform::SetWindowTitle(h, title.c_str()); 
        Onyx::Platform::Sleep(16);
    }


    printf("\n");
    window.Destroy();

    Onyx::Log::SetOutputStream(stdout);
    fclose(logFile);

    Onyx::Platform::Shutdown();

    return 0;
}