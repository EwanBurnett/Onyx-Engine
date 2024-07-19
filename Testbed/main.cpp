#include <cstdio>
#include <Onyx.h>
#include <Onyx/Core/CVar.h>

#if ONYX_PLATFORM_WINDOWS
const char* platformName = "Windows";
#elif ONYX_PLATFORM_LINUX
const char* platformName = "Linux";
#endif

int main() {
    Onyx::Log::Status("[%s]\tOnyx Version: %s\n", platformName, Onyx::GetVersionString().c_str());

    Onyx::AutoCVar_Bool bSetting("Test.Setting", "A Test CVar", false);
    bSetting.Set(true);
    bool b = bSetting.Get();

    Onyx::AutoCVar_String sSetting("Test.test", "A test CVar", "hey!");

    Onyx::CVarManager* pManager = Onyx::CVarManager::Get();
    pManager->CreateStringCVar("Test.Greeting", "A Debug Greeting Message to test CVars.", "Hello", "Hello");
    pManager->CreateStringCVar("Test.Greeting.2", "A Debug Greeting Message to test CVars.", "Hello", "Hello");
    pManager->CreateStringCVar("Test.Greeting.3", "A Debug Greeting Message to test CVars.", "Hello", "Hello");
    Onyx::AutoCVar_Bool bSetting2("Test.Greeting.4", "A Test CVar", false);

    for (int i = 0; i < 100; i++) {
        char buf[0xff];
        sprintf(buf, "Test.Obj_%d", i);
        pManager->CreateIntCVar(buf, "A Test CVar", 0, i);
    }
    auto cvars = Onyx::CVarManager::Get()->GetCVarData();
    for (auto& cvar : cvars) {
        Onyx::Log::Print("%s\n\t%s\n\t%d\n", cvar.pName->c_str(), cvar.pDescription->c_str(), cvar.type);
        switch (cvar.type) {
        case(Onyx::CVarType::BOOL):
            Onyx::Log::Print("\tInitial Value: %b\n\tCurrent Value: %b\n", *reinterpret_cast<bool*>(cvar.pInitialData), *reinterpret_cast<bool*>(cvar.pCurrentData));
            break;
        case(Onyx::CVarType::INT):
            Onyx::Log::Print("\tInitial Value: %d\n\tCurrent Value: %d\n", *reinterpret_cast<int*>(cvar.pInitialData), *reinterpret_cast<int*>(cvar.pCurrentData));
            break;
        case(Onyx::CVarType::FLOAT):
            Onyx::Log::Print("\tInitial Value: %d\n\tCurrent Value: %d\n", *reinterpret_cast<float*>(cvar.pInitialData), *reinterpret_cast<float*>(cvar.pCurrentData));
            break; 
        case(Onyx::CVarType::STRING):
            Onyx::Log::Print("\tInitial Value: %s\n\tCurrent Value: %s\n", reinterpret_cast<std::string*>(cvar.pInitialData)->c_str(), reinterpret_cast<std::string*>(cvar.pCurrentData)->c_str());
            break;
        default:
            break;
        }
    }

    //std::string sData = *reinterpret_cast<std::string*>(cvars.at(0x65).pCurrentData)        ; 


    const int* val = Onyx::CVarManager::Get()->GetIntCVar("Test.Overwriting");
    if (val) {
        printf("%d", *val);
    }

    const std::string* greeting = pManager->GetStringCVar("Test.Greeting");
    printf("%s\n", greeting->c_str());

    //Logs to stdout by default. 
    printf("This is printf!\n");
    Onyx::Log::Print("This is a Print message\n");
    Onyx::Log::Debug("This is a Debug message\n");
    Onyx::Log::Status("This is a Status Message\n");
    Onyx::Log::Warning("This is a Warning message\n");
    Onyx::Log::Success("This is a Success message\n");
    Onyx::Log::Failure("This is a Failure message\n");
    Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "This is an Error message\n");
    Onyx::Log::Fatal(__FILE__, __LINE__, __PRETTY_FUNCTION__, "This is a Fatal Error message (Triggers a breakpoint!\n");

    //Changing the logger stream
    FILE* f = fopen("LOG.txt", "a+");
    Onyx::Log::SetOutputStream(f);
    Onyx::Log::Print("%s\t%s\n", __DATE__, __TIME__);
    Onyx::Log::Print("This Print message will be printed to a file!\n");
    Onyx::Log::Debug("This Debug message will be printed to a file!\n");
    Onyx::Log::Status("This Status message will be printed to a file!\n");
    Onyx::Log::Warning("This Warning will be printed to a file!\n");
    Onyx::Log::Success("This Success message will be printed to a file!\n");
    Onyx::Log::Failure("This Failure message will be printed to a file!\n");
    Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "This Error message will be printed to both stderr and to a file!\n");
    Onyx::Log::Fatal(__FILE__, __LINE__, __PRETTY_FUNCTION__, "This Fatal Error message will be printed to both stderr and to a file!\n");

    Onyx::Log::SetOutputStream(stdout);     //ensure stream is set back to stdout. 
    fclose(f);


    return 0;
}