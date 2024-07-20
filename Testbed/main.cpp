#include <cstdio>
#include <Onyx.h>
#include <Onyx/Core/CVar.h>
#include <Onyx/Maths/Maths.h>

#if ONYX_PLATFORM_WINDOWS
const char* platformName = "Windows";
#elif ONYX_PLATFORM_LINUX
const char* platformName = "Linux";
#endif


struct Game {
    void SetMaxEntityCount(int count) {
        Onyx::Log::Status("[Game] Setting Max Entity Count to %d.\n", count);
    }
}game;

struct Settings {
    bool EnableOcclusionCulling = false;
}settings;

void ShowFrameStatistics() {
    Onyx::Log::Debug("Showing Frame Statistics.\n");
}

int main() {
    Onyx::Log::Status("[%s]\tOnyx Version: %s\n", platformName, Onyx::GetVersionString().c_str());



    Onyx::Maths::Vector3f pos = { 0.0f, 1.0f, 2.0f };
    //Define CVars

    //Define these CVars with a handle, which can be used to Get / Set their values.
    Onyx::AutoCVar_Bool showFrameStatistics("Example.Debug.ShowFrameStatistics", "Whether to show Framerate Statistics. 0: Disable, 1: Enable.", true);
    Onyx::AutoCVar_Int maxEntityCount("Example.Game.MaxEntityCount", "Controls the Maximum number of entities the game can simulate at once.", 100);

    //Define anonymous CVars, with no handle. These can only be referenced by name.
    Onyx::AutoCVar_Bool("Example.Renderer.EnableOcclusionCulling", "Whether to enable Occlusion Culling. 0: Disable, 1: Enable.", false);
    Onyx::AutoCVar_String("Example.App.LogFileName", "The name of the Application Log file. Changes to this variable will take effect on the next application load.", "log.txt");

    //Manually create a CVar through the manager. This method isn't recommended.
    Onyx::CVarManager::Get()->CreateCVar_Float("Example.World.WorldScale", "Sets the Uniform Scale of the World.", 1.0, 1.5);


    //Getting CVars

    //For CVars with a handle, simply call Get() on the handle for the value. 
    if (showFrameStatistics.Get()) {
        ShowFrameStatistics();
    }
    game.SetMaxEntityCount(maxEntityCount.Get());

    //Anonymous CVars require retrieval from the manager by name - as well as Validation. (the CVar may not exist!)
    const bool* pEnableOcclusionCulling = Onyx::CVarManager::Get()->GetCVar_Bool("Example.Renderer.EnableOcclusionCulling");
    if (pEnableOcclusionCulling != nullptr) {  //If a CVar is invalid, it will return nullptr. 
        settings.EnableOcclusionCulling = *pEnableOcclusionCulling;
    }


    //Setting CVars

    //CVars with a handle can be set by calling Set()
    showFrameStatistics.Set(false);
    maxEntityCount.Set(1000);

    //Anonymous CVars can be set through the manager
    Onyx::CVarManager::Get()->SetCVar_String("Example.App.LogFileName", "Dump.bin");


    //This example prints all current CVars to the Logger output. 
    auto cvars = Onyx::CVarManager::Get()->GetCVarData();
    for (auto& cvar : cvars) {
        Onyx::Log::Print("%s\n\t%s\n\t%d\n", cvar.pName->c_str(), cvar.pDescription->c_str(), cvar.type);
        switch (cvar.type) {
        case(Onyx::CVarType::Bool):
            Onyx::Log::Print("\tInitial Value: %s\n\tCurrent Value: %s\n", *reinterpret_cast<bool*>(cvar.pInitialData) ? "true" : "false", *reinterpret_cast<bool*>(cvar.pCurrentData) ? "true" : "false");
            break;
        case(Onyx::CVarType::Int):
            Onyx::Log::Print("\tInitial Value: %d\n\tCurrent Value: %d\n", *reinterpret_cast<int*>(cvar.pInitialData), *reinterpret_cast<int*>(cvar.pCurrentData));
            break;
        case(Onyx::CVarType::Float):
            Onyx::Log::Print("\tInitial Value: %d\n\tCurrent Value: %d\n", *reinterpret_cast<float*>(cvar.pInitialData), *reinterpret_cast<float*>(cvar.pCurrentData));
            break;
        case(Onyx::CVarType::String):
            Onyx::Log::Print("\tInitial Value: %s\n\tCurrent Value: %s\n", reinterpret_cast<std::string*>(cvar.pInitialData)->c_str(), reinterpret_cast<std::string*>(cvar.pCurrentData)->c_str());
            break;
        default:
            break;
        }
    }

    return 0;
}