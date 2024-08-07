#ifndef ONYX_PLATFORM_H
#define ONYX_PLATFORM_H
/**
* @file Platform.h
* @brief Engine Platform Layer Interface
*
* ------------------------------------------
* @author Ewan Burnett (EwanBurnettSK@outlook.com)
* @date 2024/08/06
*/
#include <cstdint> 

namespace Onyx {
    namespace Platform {

        struct PlatformInfo {
            void* pState; 
            const char* applicationName; 
        };

        typedef uint64_t WindowHandle;  //TODO: Move into Types.h 

        void Init();    
        void Shutdown(); 

        void* ZeroMemory(); 
        void* CopyMemory();
        void* SetMemory(); 

        WindowHandle CreateWindow(); 
        void DestroyWindow(Onyx::Platform::WindowHandle& window); 
        
        bool PollEvents(Onyx::Platform::WindowHandle& window); 

        void StreamOutput(); 

        void Sleep(); 
    }
}

#endif