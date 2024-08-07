//#if ONYX_PLATFORM_WINDOWS
//#if ONYX_PLATFORM_LINUX
#include <Onyx/Platform/Platform.h>
#include <string>
#include <Onyx/Core/Logger.h>
#include <Onyx/Core/CVar.h>

#include <GLFW/glfw3.h>

void Onyx::Platform::Init() {
    int result = glfwInit(); 
    if (result != GLFW_TRUE) {
        Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "Failed to initialize GLFW!\n"); 
    }
}

void Onyx::Platform::Shutdown() {
    glfwTerminate(); 
}

bool Onyx::Platform::PollEvents(WindowHandle& window) {
    GLFWwindow* pWindow = reinterpret_cast<GLFWwindow*>(window); 

    if (glfwWindowShouldClose(pWindow)) {
        return false;
    }

    glfwPollEvents();

    return true;
}

Onyx::Platform::WindowHandle Onyx::Platform::CreateWindow()
{
    GLFWwindow* pWindow;
    std::string title = "Onyx-Application"; //Onyx::Defaults::WindowTitle;
    int width = 600; //= Onyx::Defaults::WindowSize.x;
    int height = 400; //= Onyx::Defaults::WindowSize.y;
    int x = (1920 / 2) - (width / 2); //= Onyx::Defaults::WindowPos.x
    int y = (1080 / 2) - (height / 2); //= Onyy::Defaults::WindowPos.y
    int monitorIndex = 0; //= Onyx::Defaults::MonitorIndex; 

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

        const int* pHeight = Onyx::CVarManager::Get()->GetCVar_Int("Onyx.Window.Size.x");
        if (!pHeight) {
            Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "Unable to retrieve Console Variable <Onyx.Window.Size.y>\nDefaulting to height = %d.\n", width);
        }
        else {
            height = *pHeight;
        }

        const int* pPosX = Onyx::CVarManager::Get()->GetCVar_Int("Onyx.Window.Position.x");
        if (!pPosX) {
            Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "Unable to retrieve Console Variable <Onyx.Window.Position.y>\nDefaulting to x = %d.\n", x);
        }
        else {
            x = *pPosX;
        }

        const int* pPosY = Onyx::CVarManager::Get()->GetCVar_Int("Onyx.Window.Position.x");
        if (!pPosY) {
            Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "Unable to retrieve Console Variable <Onyx.Window.Position.y>\nDefaulting to y = %d.\n", y);
        }
        else {
            y = *pPosY;
        }
    }


    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); 

    GLFWmonitor* monitor; 
    {
        int count = 0;
        GLFWmonitor** monitors = glfwGetMonitors(&count);

        if (monitorIndex > count || monitorIndex < 0) {
            Onyx::Log::Warning("Invalid Monitor Index! Index was %d, when %d monitors were found!\nDefaulting to Primary monitor.\n"); 
            monitorIndex = 0; 
        }
        monitor = monitors[monitorIndex];
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        Onyx::Log::Status("Selected Monitor \"%s\" [%d]\n\tSize: (%d x %d)\n\tRefresh Rate: %dhz\n", glfwGetMonitorName(monitor), monitorIndex, mode->width, mode->height, mode->refreshRate);
    }

    pWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!pWindow) {
        Onyx::Log::Fatal(__FILE__, __LINE__, __PRETTY_FUNCTION__, "GLFW Window Creation Failed!\n");
        glfwTerminate();
        return NULL;
    }

    Onyx::Log::Success("Created Window \"%s\"\n\tHandle: [0x%8x]\n\tSize: (%d x %d)\n", title.c_str(), pWindow, width, height); 

    //glfwSetWindowMonitor(pWindow, monitor, x, y, width, height, 60);
    glfwSetWindowPos(pWindow, x, y);
    glfwShowWindow(pWindow); 

    return reinterpret_cast<WindowHandle>(pWindow);
}

void Onyx::Platform::DestroyWindow(WindowHandle& handle) {

    GLFWwindow* pWindow = reinterpret_cast<GLFWwindow*>(handle); 
    glfwDestroyWindow(pWindow); 
}

//#endif