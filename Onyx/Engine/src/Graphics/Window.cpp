#include "Onyx/Graphics/Window.h"
#include "Onyx/Platform/Platform.h"
#include "Onyx/Core/Defaults.h"
#include "Onyx/Core/Logger.h"

Onyx::Graphics::Window::Window()
{
    m_Title = ""; 
    m_Position = {}; 
    m_Size = {}; 
}

Onyx::Graphics::Window::Window(const char* title, const int posX, const int posY, const uint32_t width, const uint32_t height)
{
    m_Title = title; 
    m_Position.x = posX; 
    m_Position.y = posY; 
    m_Size.x = width; 
    m_Size.y = height; 

    Create(title, posX, posY, width, height);
}

Onyx::Graphics::Window::~Window()
{
    if (m_Handle != 0x00) {
        Log::Warning("Window Handle %x was not destroyed!\n\tPlease call Window::Destroy() before object destructor!\n"); 
    }
}

void Onyx::Graphics::Window::Create(const char* title, const int posX, const int posY, const uint32_t width, const uint32_t height)
{
    m_Handle = Platform::CreateWindow(); 
    SetTitle(m_Title);
    SetPosition(m_Position); 
    SetSize(m_Size); 
}

void Onyx::Graphics::Window::Destroy()
{
    Platform::DestroyWindow(m_Handle); 
}

void Onyx::Graphics::Window::SetPosition(int x, int y)
{
    m_Position = { x, y }; 
    Platform::SetWindowPosition(m_Handle, x, y); 
}

void Onyx::Graphics::Window::SetPosition(Maths::Vector2<int> position)
{
    m_Position = position; 
    Platform::SetWindowPosition(m_Handle, position.x, position.y); 
}

Onyx::Maths::Vector2<int> Onyx::Graphics::Window::GetPosition() const
{
    return m_Position; 
}

void Onyx::Graphics::Window::SetSize(uint32_t width, uint32_t height)
{
    m_Size = { width, height }; 
    Platform::SetWindowSize(m_Handle, width, height); 
}

void Onyx::Graphics::Window::SetSize(Maths::Vector2<uint32_t> size)
{
    m_Size = size; 
    Platform::SetWindowSize(m_Handle, size.x, size.y); 
}

Onyx::Maths::Vector2<uint32_t> Onyx::Graphics::Window::GetSize() const
{
    return m_Size;
}

void Onyx::Graphics::Window::SetTitle(const char* title)
{
    m_Title = title; 
    Platform::SetWindowTitle(m_Handle, title); 
}

const char* Onyx::Graphics::Window::GetTitle() const
{
    return m_Title; 
}

Onyx::WindowHandle Onyx::Graphics::Window::GetHandle() const
{
    if (m_Handle == 0x00) {
        Log::Warning("Window Handle is Invalid!\n");
    }
    return m_Handle; 
}
