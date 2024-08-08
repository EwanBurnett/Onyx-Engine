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
#include "../Core/Types.h"
#include <cstdint> 

namespace Onyx {
    namespace Platform {

        void Init();    
        void Shutdown(); 

        void* ZeroMemory(void* pMem, uint64_t size); 
        void* CopyMemory(void* pDst, void* pSrc, uint64_t size);
        void* SetMemory(void* pMem, uint8_t value, uint64_t size); 

        WindowHandle CreateWindow(); 
        void DestroyWindow(WindowHandle& window); 

        void SetWindowTitle(WindowHandle& window, const char* title);
        void SetWindowSize(WindowHandle& window, const uint32_t width, const uint32_t height);
        void SetWindowPosition(WindowHandle& window, const uint32_t x, const uint32_t y);

        void SetWindowVideoMode(WindowHandle& window, const VideoMode& mode); 

        bool PollEvents(WindowHandle window); 

        void Sleep(uint64_t milliseconds); 
    }
}

#endif