#include <cstdio>
#include <Onyx.h>
#include <Onyx/Core/CVar.h>
#include <Onyx/Maths/Maths.h>
#include <Onyx/Memory/Memory.h>
#include <Onyx/Memory/StackAllocator.h>
#include <Onyx/Memory/PoolAllocator.h>
#include <cstring>
#include <cstdio>
#include <Onyx/Platform/Platform.h>

using namespace Onyx;

int main() {
    Onyx::Init();

    int b = 0; 
    Onyx::Platform::Init(); 
    Onyx::Platform::WindowHandle hwnd = Onyx::Platform::CreateWindow(); 

    while (Onyx::Platform::PollEvents(hwnd)) {
        static int a = 0; 
        a++;
        //printf("\r%d", a++);
    }

    Onyx::Platform::DestroyWindow(hwnd); 

    printf("\n");

#if ONYX_DEBUG
    Onyx::CVarManager::Get()->SetCVar_Bool("Onyx.Log.EnableForwarding", true);
#endif
    FILE* logFile = fopen("Log.txt", "a+");
    Onyx::Log::SetOutputStream(logFile);

    Onyx::Memory::StackAllocator stack(Onyx::Memory::MEGABYTES(512), 32);
    Onyx::Memory::StackAllocator::Marker marker = stack.Top();

    void* pPoolMem = stack.Alloc(64 * 10000);
    Onyx::Memory::PoolAllocator pool(pPoolMem, 64, 10000); 

    for (int i = 0; i < 10000; i++) {
        void* pd = pool.Alloc();
        *(Onyx::Maths::Matrix4x4<float>*)pd = {};

        printf("\rPool %d chunks Allocated out of %u (%f / 1.0)!", pool.NumAllocated(), pool.Size(), (float)pool.NumAllocated() / (float)pool.Size());

        if (i % 2) {
            pool.Free(pd);
        }
    }

    printf("\n");

    for (uint64_t i = 0; i < 1000; i++) {

        printf("\rStack %d bytes Allocated out of %u bytes (%f / 1.0)!", stack.BytesAllocated(), stack.Capacity(), (float)stack.BytesAllocated() / (float)stack.Capacity());
        void* pMatrices = stack.Alloc(sizeof(Onyx::Maths::Matrix4x4<float>) * 10, Onyx::Memory::DEFAULT_ALIGNMENT); // This should allocate 64000 bytes from the stack. (plus alignment requirements)
        for (int j = 0; j < 1000; j++) {
            static_cast<Onyx::Maths::Matrix4x4<float>*>(pMatrices)[j] = {};
        }

        int a = 1;


        //Explicit delete()
        for (int j = 0; j < 1000; j++) {
            //pMat[j].~Onyx::Maths::Matrix4x4<float>();
        }
    }

    stack.Clear();

    Onyx::Log::SetOutputStream(stdout);
    fclose(logFile);

    return 0;
}