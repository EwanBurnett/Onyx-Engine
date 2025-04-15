#include <Onyx.h>
#include <Onyx/Platform/Platform.h>
#include <Onyx/Core/CVar.h>
#include <Onyx/Graphics/Window.h>
#include <cstdio>
#include <cstring>
#include <cstdio>
#include <Onyx/Core/String.h>
#include <Onyx/Core/Timer.h>
#include <Onyx/Core/Event.h>
#include <Onyx/Memory/PoolAllocator.h>

enum class EEvents {
    L, 
};
class TestEvent : public Onyx::Event<EEvents>
{
public: 
    TestEvent() : Event<EEvents>(EEvents::L, "Debug Event") {}; 
    virtual ~TestEvent() {}

    int width = 0; 
    int height = 0; 
};

void Foo(Onyx::Event<EEvents> event) {
    Onyx::Log::Status("Foo!\n"); 
}

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
    title.Format("Testbed - Onyx [%s] %s", Onyx::GetBranchName().c_str(), Onyx::GetVersionString().c_str());

    Onyx::Graphics::Window window(title.c_str(), 400, 200, 1280, 720);
    auto h = window.GetHandle();
    Onyx::Platform::SetWindowIcon(h, "Resources/Onyx_Icon_256x256.ico");
 
    Onyx::Timer timer;
    timer.Reset();
    timer.Start();

    Onyx::EventDispatcher<EEvents> dispatcher; //TODO: I hate this interface! Refactor!                                                                                                                                                                                                
    dispatcher.AddListener(EEvents::L, Foo);


    while (Onyx::Platform::PollEvents(window.GetHandle())) {
        static uint64_t frameIdx = 0;
        frameIdx++; 

        static double acc = 0.0;
        timer.Tick();
        double dtms = timer.DeltaTime();
        acc += dtms;

        if (acc >= (1.0 / 20.0)) {
            acc = 0.0;

            const uint64_t fps = 1.0 / dtms; 
            Onyx::Log::Print("\r                                         "); 
            Onyx::Log::Print("\rFrame %d\t%8.8fms\t%dfps", frameIdx, dtms, fps);
            title.Format("%d FPS - Testbed - Onyx [%s] %s", fps, Onyx::GetBranchName().c_str(), Onyx::GetVersionString().c_str());
            Onyx::Platform::SetWindowTitle(h, title.c_str());
        }
         
        /*
        if (dtms < (1.0 / 60.0)) {
            uint64_t sleepTimeMS = static_cast<uint64_t>(((1.0 / 60.0) - dtms) * 1000.0);
            Onyx::Platform::Sleep(sleepTimeMS);
        }
        */
    }


    printf("\n");
    window.Destroy();

    Onyx::Log::SetOutputStream(stdout);
    fclose(logFile);

    Onyx::Platform::Shutdown();

    return 0;
}