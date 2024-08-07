#include "Onyx/Memory/StackAllocator.h"
#include <assert.h>
#include <cstring> 
#include <new>
#include "Onyx/Core/Logger.h"
#include "Onyx/Platform/Platform.h"
#include "Onyx/Core/Defaults.h"

Onyx::Memory::StackAllocator::StackAllocator(void* pData, const uint64_t capacity, const uint64_t alignment)
{
    m_pData = pData;
    m_Capacity = capacity;
    m_Top = 0;
    m_bInPlace = true;   //The allocator was supplied with external memory; We don't want to free it from the allocator. 

#if ONYX_DEBUG
    Platform::SetMemory(m_pData, Defaults::InvalidMemoryValue, m_Capacity);
    //memset((char*)m_pData, 0xde, m_Capacity);
#endif
}

Onyx::Memory::StackAllocator::StackAllocator(const uint64_t size, const uint64_t alignment)
{
    m_pData = AllocAligned(size, alignment); //Allocate data for the stack
    m_Top = 0;
    m_Capacity = size;
    m_bInPlace = false;
#if ONYX_DEBUG
    Platform::SetMemory(m_pData, Defaults::InvalidMemoryValue, m_Capacity);
    //memset((char*)m_pData, 0xde, m_Capacity);
#endif
}


Onyx::Memory::StackAllocator::StackAllocator(StackAllocator&& other) noexcept{
    this->m_bInPlace = other.m_bInPlace; 
    this->m_pData = other.m_pData; 
    this->m_Capacity = other.m_Capacity; 
    this->m_Top = other.m_Top; 
}

Onyx::Memory::StackAllocator::~StackAllocator()
{
    if (!m_bInPlace) {
        FreeAligned(m_pData); 
    }
}

void* Onyx::Memory::StackAllocator::Alloc(const uint64_t size, const uint64_t alignment)
{
    if (!(size <= m_Capacity - m_Top)) {
        Onyx::Log::Fatal(__FILE__, __LINE__, __PRETTY_FUNCTION__, "Bad Alloc!\n%d(+ %d) bytes requested, but Available Memory was %d bytes!\n", size, alignment - 1, (m_Capacity - m_Top));
    }

    char* pData = (char*)m_pData + m_Top;

    char* pAlloc = pData;
    m_Top += size + (alignment - 1);
    pAlloc = AlignPointer<char>(pData, alignment);

#if ONYX_DEBUG
    Platform::SetMemory(pData, Defaults::AllocatedMemoryValue, pAlloc - pData);
    Platform::ZeroMemory(pAlloc, size);
    //memset(pData, 0xFF, pAlloc - pData);
    //memset(pAlloc, 0x00, size);
#endif
    return pAlloc;
}


void Onyx::Memory::StackAllocator::FreeToMarker(const Marker marker)
{
    assert(marker <= m_Top);
    m_Top = marker;

#if ONYX_DEBUG
    Platform::SetMemory((char*)m_pData + m_Top, Defaults::FreedMemoryValue, marker - m_Top);
    //memset((char*)m_pData + m_Top, 0xcc, marker - m_Top);;
#endif
}

Onyx::Memory::StackAllocator::Marker Onyx::Memory::StackAllocator::Top() const
{
    return m_Top;
}

uint64_t Onyx::Memory::StackAllocator::Capacity() const
{
    return m_Capacity;
}

uint64_t Onyx::Memory::StackAllocator::BytesAllocated() const
{
    return Capacity() - (Capacity() - Top());
}

void Onyx::Memory::StackAllocator::Clear()
{
    FreeToMarker(0x00);
}
