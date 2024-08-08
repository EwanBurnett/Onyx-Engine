#include "Onyx.h"
#include <Onyx/Core/Logger.h>

void Onyx::Init()
{
    Onyx::Log::Status("Onyx Version: %s\n", Onyx::GetVersionString().c_str());

    //Define all Configuration CVars
    AutoCVar_Bool("Onyx.Log.EnableForwarding", "Controls whether to forward log output to `stdout`, when the output stream is changed to something else. 0 to disable, 1 to enable.", false);
    AutoCVar_String("Onyx.Application.Name", "The Name of the Application.", "Onyx-Application"); 
    AutoCVar_Int("Onyx.Window.Size.x", "The Initial Width of the Application Window.", 600);
    AutoCVar_Int("Onyx.Window.Size.y", "The Initial Height of the Application Window.", 400);
}
