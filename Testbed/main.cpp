#include <cstdio>
#include <Onyx.h>

#if ONYX_PLATFORM_WINDOWS
const char* platformName = "Windows";
#elif ONYX_PLATFORM_LINUX
const char* platformName = "Linux";
#endif

int main() {
    Onyx::Log::Message("[%s]\tOnyx Version: %s\n", platformName, Onyx::GetVersionString().c_str());

    //Logs to stdout by default. 
    printf("This is printf!\n");
    Onyx::Log::Print("This is a Print message\n");
    Onyx::Log::Debug("This is a Debug message\n");
    Onyx::Log::Message("This is a Message\n");
    Onyx::Log::Warning("This is a Warning message\n");
    Onyx::Log::Success("This is a Success message\n");
    Onyx::Log::Failure("This is a Failure message\n");
    Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "This is an Error message\n");

    //Changing the logger stream
    FILE* f = fopen("LOG.txt", "a+");
    Onyx::Log::SetOutputStream(f);
    Onyx::Log::Print("%s\t%s\n", __DATE__, __TIME__);
    Onyx::Log::Debug("This Debug message will be printed to a file!\n");
    Onyx::Log::Message("This message will be printed to a file!\n");
    Onyx::Log::Warning("This Warning will be printed to a file!\n");;
    Onyx::Log::Success("This Success message will be printed to a file!\n");
    Onyx::Log::Failure("This Failure message will be printed to a file!\n");
    Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "This Error message will be printed to both stderr and to a file!\n");
    Onyx::Log::Fatal(__FILE__, __LINE__, __PRETTY_FUNCTION__, "This is a Fatal Error message (Triggers a breakpoint!)\n");

    Onyx::Log::SetOutputStream(stdout);     //ensure stream is set back to stdout. 
    fclose(f);


    return 0;
}