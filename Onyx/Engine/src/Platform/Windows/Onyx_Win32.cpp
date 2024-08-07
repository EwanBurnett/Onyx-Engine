#if ONYX_PLATFORM_WINDOWS_E
#include <Onyx/Platform/Platform.h>
#include <sdkddkver.h>

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

#include <Onyx/Core/Logger.h>
#include <Onyx/Core/CVar.h>
#include <Onyx/Core/Utility.h>

//_ImageBase represents the module's DOS header - functionally equivalent to the HINSTANCE of the current module.
//This way, the MODULE_INSTANCE variable can represent the HINSTANCE of the module being linked to. 
extern "C" IMAGE_DOS_HEADER __ImageBase;
#define MODULE_INSTANCE ((HINSTANCE)&__ImageBase)

// WINDOWS PLATFORM METHODS -------------------------------------------------

LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
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
    //Attempt to retrieve the Window Class Name from our CVar Manager.
    std::string windowClassName;
    const std::string* pWindowClassName = Onyx::CVarManager::Get()->GetCVar_String("Onyx.Application.ApplicationName");
    if (!pWindowClassName) {
        Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "Unable to retrieve Window Class Name!\nDefaulting to \"Onyx-Application\"\n");
        windowClassName = "Onyx-Application";
    }
    else {
        windowClassName = *pWindowClassName;
    }

    const int* defaultWidth = Onyx::CVarManager::Get()->GetCVar_Int("Onyx.Application.DefaultWindowWidth");
    const int* defaultHeight = Onyx::CVarManager::Get()->GetCVar_Int("Onyx.Application.DefaultWindowHeight");

    Onyx::Log::Status("[Win32]\tRegistering Window Class %s.\n", windowClassName.c_str());

    //Convert the window class name to a Wide String, for internal use
    //const std::wstring windowClassName = Onyx::StringToWString(*windowClassName); 
    const std::string windowTitle = "Onyx Window";

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
        wnd.lpszClassName = windowClassName.c_str();
        wnd.cbWndExtra = sizeof(LONG_PTR);
    }

    RegisterClassEx(&wnd);

    //Style the window
    const uint32_t windowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

    //Adjust the size of the client area of the window based on the style. 

    RECT windowRect{ 0, 0, (LONG)*defaultWidth, (LONG)*defaultHeight };
    AdjustWindowRect(&windowRect, (DWORD)windowStyle, FALSE);

    const uint16_t width = windowRect.right - windowRect.left;
    const uint16_t height = windowRect.bottom - windowRect.top;

    Onyx::Log::Status("[Win32]\tCreating Window \"%s\":\n\tPosition: (%d, %d)\n\tSize: %dpx x %dpx\n", windowTitle.c_str(), 0, 0, width, height);

    HWND hWnd = CreateWindow(windowClassName.c_str(), windowTitle.c_str(), windowStyle, 0, 0, width, height, nullptr, nullptr, MODULE_INSTANCE, nullptr);

    printf("[Win32]\tRegistering Raw Input Devices.\n");
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


void DestroyWindow_Impl(Onyx::Platform::WindowHandle& window) {
    HWND hwnd = reinterpret_cast<HWND>(window);
    DestroyWindow(hwnd);

    window = 0x00; //Invalidate the Handle
}

// INTERFACE METHODS --------------------------------------------------------

void Onyx::Platform::Init()
{
    Onyx::Log::Status("[Win32]\tInitializing for Windows Platform.");
}


#pragma push_macro("CreateWindow")
#undef CreateWindow
Onyx::Platform::WindowHandle Onyx::Platform::CreateWindow()
{
    return reinterpret_cast<WindowHandle>(CreateWindow_Impl());
}
#pragma pop_macro("CreateWindow")

#pragma push_macro("DestroyWindow")
#undef DestroyWindow
void Onyx::Platform::DestroyWindow(Onyx::Platform::WindowHandle& window)
{
    DestroyWindow_Impl(window);
}
#pragma pop_macro("DestroyWindow")

bool Onyx::Platform::PollEvents(Onyx::Platform::WindowHandle& window)
{
    MSG msg{};
    while (PeekMessage(&msg, reinterpret_cast<HWND>(window), 0, 0, PM_REMOVE)) {

        //Exit the application if a quit message has been posted.
        if (msg.message == WM_QUIT || msg.message == WM_CLOSE) {
            return false;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}
#endif
