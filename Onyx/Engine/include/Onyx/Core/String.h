#ifndef ONYX_CORE_STRING_H
#define ONYX_CORE_STRING_H

#include "Logger.h"
#include <string> 
#include <cstdarg> 

namespace Onyx {
    class String {
    public: 
        String(); 
        String(const char* fmt); 
        template<typename ... Args> 
        String(const char* fmt, Args ... args) {
            Format(fmt, args...)
        }
        
        uint64_t Hash(); 

        template<typename ... Args> 
        void Format(const char* fmt, Args ... args) {
            size_t stringSize = std::snprintf(nullptr, 0, fmt, args...);

            if (stringSize <= 0) {
                Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "String size was invalid!\n"); 
                m_String = ""; 
            }

            m_String.resize(stringSize + 1); 
            std::snprintf(m_String.data(), stringSize + 1, fmt, args...);

        }

        uint64_t Size() const; 
        const char* c_str() const;


    private: 
        std::string m_String; 
    };
}

#endif