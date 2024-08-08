#if ONYX_PLATFORM_WINDOWS

#include <Onyx/Platform/Platform.h>

#include <Onyx/Core/Logger.h>
#include <Onyx/Core/CVar.h>
#include <Onyx/Core/Utility.h>
#include <Onyx/Core/Defaults.h>

//Target Windows 7 or later
#define _WIN32_WINNT 0x0601

//These #Defines disable unused windows features.
//They are optional, but omitting them will increase build times.
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE

#define NOMINMAX

#include <windows.h>
#include <hidusage.h>
#include <sdkddkver.h>
#include <string> 
#include <thread>
#include <chrono>

//_ImageBase represents the module's DOS header - functionally equivalent to the HINSTANCE of the current module.
//This way, the MODULE_INSTANCE variable can represent the HINSTANCE of the module being linked to. 
extern "C" IMAGE_DOS_HEADER __ImageBase;
#define MODULE_INSTANCE ((HINSTANCE)&__ImageBase)

// WINDOWS PLATFORM METHODS -------------------------------------------------

LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    //Onyx::Log::Status("Processing Message %d\n", msg); 


    switch (msg)
    {
    case WM_DESTROY:
    case WM_CLOSE:
        PostQuitMessage(0x00);
        return 0;
    case WM_MOVE:
        break;
    case WM_SIZE:
        break;
    default:
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}


HWND CreateWindow_Impl() {
    std::string title = Onyx::Defaults::WindowTitle;
    int width = Onyx::Defaults::WindowSize.x;
    int height = Onyx::Defaults::WindowSize.y;
    int monitorIndex = Onyx::Defaults::MonitorIndex;


    //Retrieve Values from Console Variables
    {
        const std::string* pTitle = Onyx::CVarManager::Get()->GetCVar_String("Onyx.Application.Name");
        if (!pTitle) {
            Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "Unable to retrieve Console Variable <Onyx.Application.Name>!\nDefaulting to \"%s\"\n", title.c_str());
        }
        else {
            title = *pTitle;
        }

        const int* pWidth = Onyx::CVarManager::Get()->GetCVar_Int("Onyx.Window.Size.x");
        if (!pWidth) {
            Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "Unable to retrieve Console Variable <Onyx.Window.Size.x>\nDefaulting to width = %d.\n", height);
        }
        else {
            width = *pWidth;
        }

        const int* pHeight = Onyx::CVarManager::Get()->GetCVar_Int("Onyx.Window.Size.y");
        if (!pHeight) {
            Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "Unable to retrieve Console Variable <Onyx.Window.Size.y>\nDefaulting to height = %d.\n", width);
        }
        else {
            height = *pHeight;
        }
    }


    Onyx::Log::Status("[Win32]\tRegistering Window Class %s.\n", title.c_str());

    //Convert the window class name to a Wide String, for internal use
    //const std::wstring title = Onyx::StringToWString(*title); 

    //Register a new Window Class
    WNDCLASSEX wnd = {};
    {
        ZeroMemory(&wnd, sizeof(wnd));
        wnd.cbSize = sizeof(WNDCLASSEX);
        wnd.style = CS_OWNDC;
        wnd.lpfnWndProc = WndProc;
        wnd.hInstance = MODULE_INSTANCE;
        wnd.hIcon = nullptr;
        wnd.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wnd.lpszClassName = title.c_str();
        wnd.cbWndExtra = sizeof(LONG_PTR);
    }

    RegisterClassEx(&wnd);

    //Style the window
    const uint32_t windowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

    //Adjust the size of the client area of the window based on the style. 

    RECT windowRect{ 0, 0, (LONG)width, (LONG)height };
    AdjustWindowRect(&windowRect, (DWORD)windowStyle, FALSE);

    const uint16_t windowWidth = windowRect.right - windowRect.left;
    const uint16_t windowHeight = windowRect.bottom - windowRect.top;

    int windowPosX = 0;
    int windowPosY = 0;

    {
        const int monitorSizeX = 1920; //TODO: Load dynamically
        const int monitorSizeY = 1080;

        windowPosX = (monitorSizeX / 2) - (windowWidth / 2);
        windowPosY = (monitorSizeY / 2) - (windowHeight / 2);
    }


    HWND hWnd = CreateWindow(title.c_str(), title.c_str(), windowStyle, windowPosX, windowPosY, windowWidth, windowHeight, nullptr, nullptr, MODULE_INSTANCE, nullptr);
    Onyx::Log::Success("[Win32] Created Window \"%s\"\n\tHandle: [0x%8x]\n\tSize: (%d x %d)\n", title.c_str(), hWnd, width, height);

    Onyx::Log::Status("[Win32]\tRegistering Raw Input Devices.\n");
    //Register raw input devices - 0 = mouse, 1 = keyboard
    RAWINPUTDEVICE rid[2] = {};
    rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
    rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
    rid[0].dwFlags = RIDEV_INPUTSINK;
    rid[0].hwndTarget = hWnd;

    rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
    rid[1].usUsage = HID_USAGE_GENERIC_KEYBOARD;
    rid[1].dwFlags = RIDEV_INPUTSINK;
    rid[1].hwndTarget = hWnd;

    bool rawInputStatus = RegisterRawInputDevices(rid, 2, sizeof(rid[0]));

    return hWnd;
}


void DestroyWindow_Impl(Onyx::WindowHandle& window) {
    HWND hwnd = reinterpret_cast<HWND>(window);
    DestroyWindow(hwnd);

    window = 0x00; //Invalidate the Handle
}

// INTERFACE METHODS --------------------------------------------------------

void Onyx::Platform::Init()
{
    Onyx::Log::Status("[Win32]\tInitializing for Platform \"%s\".\n", Onyx::Defaults::PlatformName);
}

void Onyx::Platform::Shutdown() {
    Onyx::Log::Status("[Win32]\tShutting Down %s Platform Backend.");
}

#pragma push_macro("ZeroMemory")
#undef ZeroMemory
void* Onyx::Platform::ZeroMemory(void* pMem, uint64_t size)
{
    for (uint64_t i = 0; i < size; i++) {
        static_cast<char*>(pMem)[i] = 0;
    }
    return pMem;
}
#pragma pop_macro("ZeroMemory")

#pragma push_macro("CopyMemory")
#undef CopyMemory
void* Onyx::Platform::CopyMemory(void* pDst, void* pSrc, uint64_t size)
{
    return memcpy(pDst, pSrc, size);
}
#pragma pop_macro("CopyMemory")

void* Onyx::Platform::SetMemory(void* pMem, uint8_t value, uint64_t size)
{
    for (uint64_t i = 0; i < size; i++) {
        static_cast<char*>(pMem)[i] = value;
    }
    return pMem;
}


#pragma push_macro("CreateWindow")
#undef CreateWindow
Onyx::WindowHandle Onyx::Platform::CreateWindow()
{
    return reinterpret_cast<WindowHandle>(CreateWindow_Impl());
}
#pragma pop_macro("CreateWindow")

#pragma push_macro("DestroyWindow")
#undef DestroyWindow
void Onyx::Platform::DestroyWindow(WindowHandle& window)
{
    DestroyWindow_Impl(window);
}
#pragma pop_macro("DestroyWindow")

void Onyx::Platform::SetWindowTitle(WindowHandle& window, const char* title)
{
    HWND hwnd = reinterpret_cast<HWND>(window); 
    SetWindowText(hwnd, title); 
}

void Onyx::Platform::SetWindowSize(WindowHandle& window, const uint32_t width, const uint32_t height)
{
    HWND hwnd = reinterpret_cast<HWND>(window); 
    SetWindowPos(hwnd, nullptr, 0, 0, width, height, SWP_NOMOVE); 
}

void Onyx::Platform::SetWindowPosition(WindowHandle& window, const uint32_t x, const uint32_t y)
{
    HWND hwnd = reinterpret_cast<HWND>(window); 
    SetWindowPos(hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE); 
}

bool Onyx::Platform::PollEvents(Onyx::WindowHandle window)
{
    MSG msg{};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        //Exit the application if a quit message has been posted.
        if (msg.message == WM_QUIT || msg.message == WM_CLOSE) {
            return false;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);


    }

    return true;
}

void Onyx::Platform::Sleep(uint64_t milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds)); 
}

#endif
