#include "Onyx/Core/String.h"
#include <unordered_map>

Onyx::String::String()
{
}

Onyx::String::String(const char* fmt)
{
    m_String = fmt;
}

      
uint64_t Onyx::String::Hash()
{
    return std::hash<std::string>{}(m_String);  //TODO: Use custom hashing function
}

uint64_t Onyx::String::Size() const
{
    return m_String.size();
}

const char* Onyx::String::c_str() const
{
    return m_String.c_str();
}
