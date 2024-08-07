#include "Onyx.h"

void Onyx::Init()
{
    AutoCVar_Bool("Engine.Log.EnableForwarding", "Controls whether to forward log output to `stdout`, when the output stream is changed to something else. 0 to disable, 1 to enable.", false);
    AutoCVar_String("Onyx.Application.ApplicationName", "The Internal Application name.", "Onyx-Application"); 
    AutoCVar_Int("Onyx.Application.DefaultWindowWidth", "The Default Width of the Window.", 600);
    AutoCVar_Int("Onyx.Application.DefaultWindowHeight", "The Default Height of the Window.", 400);
}
