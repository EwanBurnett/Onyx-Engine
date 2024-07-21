#include "Onyx.h"

void Onyx::Init()
{
    AutoCVar_Bool("Engine.Log.EnableForwarding", "Controls whether to forward log output to `stdout`, when the output stream is changed to something else. 0 to disable, 1 to enable.", false);
}
