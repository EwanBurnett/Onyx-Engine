#include <cstdio>
#include <Onyx.h>
#include <Onyx/Core/CVar.h>
#include <Onyx/Maths/Maths.h>
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

    Onyx::Memory::StackAllocator stack(Onyx::Memory::MEGABYTES(512), 32);
    Onyx::Memory::StackAllocator::Marker marker = stack.Top(); 
    stack.Alloc(32); 

    //void* pMem = stack.Alloc(Onyx::Memory::MEGABYTES(0xa), 64); 
    //Onyx::Memory::StackAllocator subStack(pMem, Onyx::Memory::MEGABYTES(0xa)); 
    //void* pMem3 = subStack.Alloc(Onyx::Memory::KILOBYTES(20)); 
    //memset(pMem3, 0xaa, Onyx::Memory::KILOBYTES(10)); 
    //void* pMem2 = stack.Alloc(Onyx::Memory::BYTES(12), 64); 


    for (uint64_t i = 0; i < 100; i++) {

        printf("\rStack %d bytes Allocated out of %u bytes (%f / 1.0)!", stack.BytesAllocated(), stack.Capacity(), (float)stack.BytesAllocated() / (float)stack.Capacity()); 
        //auto* pQuat = stack.Alloc<Onyx::Maths::Quaternion, double, Onyx::Maths::Vector3f>(64, 0, 1.0, Onyx::Maths::Vector3f{ 2.0f, 3.0f, 4.0f });
        auto* pMat = stack.Alloc<Onyx::Maths::Matrix4x4<float>>(10000, Onyx::Memory::DEFAULT_ALIGNMENT);
        

        //printf("SubStack %d bytes Alocated out of %d bytes (%f / 1.0)!\n", subStack.BytesAllocated(), subStack.Capacity(), (float)subStack.BytesAllocated() / (float)subStack.Capacity()); 
        int a = 0; 
   }

    stack.Clear(); 

    Onyx::Log::SetOutputStream(stdout); 
    fclose(logFile); 

    return 0;
}