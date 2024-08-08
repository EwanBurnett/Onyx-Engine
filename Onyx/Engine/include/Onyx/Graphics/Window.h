#ifndef ONYX_GRAPHICS_WINDOW_H
#define ONYX_GRAPHICS_WINDOW_H
#include "../Maths/Vector2.h"
#include "Onyx/Core/Types.h"
#include <cstdint> 
namespace Onyx {
    namespace Graphics {
        class Window {
        public: 
            Window();
            Window(const char* title, const int posX, const int posY, const uint32_t width, const uint32_t height); 
            ~Window(); 

            void Create(const char* title, const int posX, const int posY, const uint32_t width, const uint32_t height); 
            void Destroy(); 

            void SetPosition(int x, int y); 
            void SetPosition(Maths::Vector2<int> position); 
            Maths::Vector2<int> GetPosition() const; 

            void SetSize(uint32_t width, uint32_t height); 
            void SetSize(Maths::Vector2<uint32_t> size); 
            Maths::Vector2<uint32_t> GetSize() const; 

            void SetTitle(const char* title); 
            const char* GetTitle() const; 

            WindowHandle GetHandle() const; 

        private:
            const char* m_Title; 
            Maths::Vector2<int> m_Position; 
            Maths::Vector2<uint32_t> m_Size; 
            WindowHandle m_Handle; 
        };
    }
}
#endif