#include <cstdio>
#include <Onyx.h>
#include <Onyx/Core/CVar.h>
#include <Onyx/Memory/Memory.h>
#include <Onyx/Memory/StackAllocator.h>
#include <cstring>
#include <cstdio>

#if ONYX_PLATFORM_WINDOWS
const char* platformName = "Windows";
#elif ONYX_PLATFORM_LINUX
const char* platformName = "Linux";
#endif

using namespace Onyx;

int main() {
    Onyx::Init();
 
    Onyx::Log::Status("[%s]\tOnyx Version: %s\n", platformName, Onyx::GetVersionString().c_str());

#if ONYX_DEBUG
    Onyx::CVarManager::Get()->SetCVar_Bool("Engine.Log.EnableForwarding", true);
#endif
    FILE* logFile = fopen("Log.txt", "a+");
    Onyx::Log::SetOutputStream(logFile);

    Onyx::Memory::StackAllocator stack(Onyx::Memory::MEGABYTES(0xf));
    Onyx::Memory::StackAllocator::Marker marker = stack.Top(); 

    void* pMem = stack.Alloc(Onyx::Memory::MEGABYTES(0xa), 64); 
    Onyx::Memory::StackAllocator subStack(pMem, Onyx::Memory::MEGABYTES(0xa)); 
    void* pMem3 = subStack.Alloc(Onyx::Memory::KILOBYTES(20)); 
    memset(pMem3, 0xaa, Onyx::Memory::KILOBYTES(10)); 
    void* pMem2 = stack.Alloc(Onyx::Memory::BYTES(12), 64); 

    printf("Stack %d bytes Alocated out of %d bytes (%f / 1.0)!\n", stack.BytesAllocated(), stack.Capacity(), (float)stack.BytesAllocated() / (float)stack.Capacity()); 
    printf("SubStack %d bytes Alocated out of %d bytes (%f / 1.0)!\n", subStack.BytesAllocated(), subStack.Capacity(), (float)subStack.BytesAllocated() / (float)subStack.Capacity()); 

    stack.FreeToMarker(marker); 

    while (true) {
        int a = 0; 
   }

    Onyx::Log::SetOutputStream(stdout); 
    fclose(logFile); 

    return 0;
}