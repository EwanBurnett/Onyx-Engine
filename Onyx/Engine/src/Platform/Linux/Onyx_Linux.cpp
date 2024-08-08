#if ONYX_PLATFORM_LINUX
#include <Onyx/Core/Logger.h>
#include <Onyx/Core/CVar.h>
#include <Onyx/Core/Defaults.h>
#include <Onyx/Platform/Platform.h>
#include <GLFW/glfw3.h>
#include <string>
#include <thread>
#include <chrono> 

void Onyx::Platform::Init() {
    Onyx::Log::Status("[Linux]\tInitializing %s Platform Backend.\n", /*Onyx::Defaults::PlatformName*/ "TEST");
    int result = glfwInit();
    if (result != GLFW_TRUE) {
        Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "Failed to initialize GLFW!\n");
    }
}

void Onyx::Platform::Shutdown() {
    Onyx::Log::Status("[Linux]\tShutting Down %s Platform Backend.");
    glfwTerminate();
}

void* Onyx::Platform::ZeroMemory(void* pMem, uint64_t size)
{
    for (uint64_t i = 0; i < size; i++) {
        static_cast<char*>(pMem)[i] = 0;
    }
    return pMem;
}

void* Onyx::Platform::CopyMemory(void* pDst, void* pSrc, uint64_t size)
{
    return memcpy(pDst, pSrc, size);
}

void* Onyx::Platform::SetMemory(void* pMem, uint8_t value, uint64_t size)
{
    for (uint64_t i = 0; i < size; i++) {
        static_cast<char*>(pMem)[i] = value;
    }
    return pMem;
}

void Onyx::Platform::SetWindowTitle(WindowHandle& window, const char* title)
{
    GLFWwindow* pWindow = reinterpret_cast<GLFWwindow*>(window);
    glfwSetWindowTitle(pWindow, title);
}

void Onyx::Platform::SetWindowSize(WindowHandle& window, const uint32_t width, const uint32_t height)
{
    GLFWwindow* pWindow = reinterpret_cast<GLFWwindow*>(window);
    glfwSetWindowSize(pWindow, width, height);
}

void Onyx::Platform::SetWindowPosition(WindowHandle& window, const uint32_t x, const uint32_t y)
{
    GLFWwindow* pWindow = reinterpret_cast<GLFWwindow*>(window);
    glfwSetWindowPos(pWindow, x, y);
}

Onyx::WindowHandle Onyx::Platform::CreateWindow()
{
    GLFWwindow* pWindow;
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

    //glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    pWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!pWindow) {
        Onyx::Log::Fatal(__FILE__, __LINE__, __PRETTY_FUNCTION__, "GLFW Window Creation Failed!\n");
        glfwTerminate();
        return NULL;
    }

    Onyx::Log::Success("[Linux] Created Window \"%s\"\n\tHandle: [0x%8x]\n\tSize: (%d x %d)\n", title.c_str(), pWindow, width, height);

    GLFWmonitor* monitor;
    {
        int count = 0;
        GLFWmonitor** monitors = glfwGetMonitors(&count);

        if (monitorIndex > count || monitorIndex < 0) {
            Onyx::Log::Warning("[Linux] Invalid Monitor Index! Index was %d, when %d monitors were found!\nDefaulting to Primary monitor.\n");
            monitorIndex = 0;
        }
        monitor = monitors[monitorIndex];
    }
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    Onyx::Log::Status("[Linux] Selected Monitor \"%s\" [%d]\n\tSize: (%d x %d)\n\tRefresh Rate: %dhz\n", glfwGetMonitorName(monitor), monitorIndex, mode->width, mode->height, mode->refreshRate);

    int posX = (mode->width / 2) - (width / 2);     //Center the window by default. 
    int posY = (mode->height / 2) - (height / 2);
    glfwSetWindowPos(pWindow, posX, posY);
    glfwShowWindow(pWindow);

    return reinterpret_cast<WindowHandle>(pWindow);
}

void Onyx::Platform::DestroyWindow(WindowHandle& handle) {

    GLFWwindow* pWindow = reinterpret_cast<GLFWwindow*>(handle);
    glfwDestroyWindow(pWindow);
}

bool Onyx::Platform::PollEvents(WindowHandle window) {
    GLFWwindow* pWindow = reinterpret_cast<GLFWwindow*>(window);

    if (glfwWindowShouldClose(pWindow)) {
        return false;
    }

    glfwPollEvents();

    glfwSwapBuffers(pWindow); 
    return true;
}

void Onyx::Platform::Sleep(uint64_t milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

#endif