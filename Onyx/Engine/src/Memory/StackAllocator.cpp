#include "Onyx/Memory/StackAllocator.h"
#include <assert.h>
#include <cstring> 
#include <new>

Onyx::Memory::StackAllocator::StackAllocator(void* pData, const uint64_t capacity, const uint64_t alignment)
{
    m_pData = pData; 
    m_Capacity = capacity; 
    m_Alignment = alignment; 
    m_Top = 0; 
}

Onyx::Memory::StackAllocator::StackAllocator(const uint64_t size,  const uint64_t alignment)
{
    m_Alignment = alignment; 
    m_pData = new char[size]; //Allocate data for the stack
    m_Top = 0; 
    m_Capacity = size; 
#if ONYX_DEBUG
    memset((char*)m_pData, 0xde, m_Capacity); 
#endif
}

Onyx::Memory::StackAllocator::~StackAllocator()
{
    delete[] m_pData; 
    //delete[] m_pData, std::align_val_t{m_Alignment}; 
}

void* Onyx::Memory::StackAllocator::Alloc(const uint64_t size, const uint64_t alignment)
{
    assert(size <= m_Capacity - m_Top);
    //uint64_t allocSize = size + (alignment - 1); 
    void* pData = (char*)m_pData + m_Top;
    //void* pDataAligned = (void*)AlignAddress((uintptr_t)pData, alignment);
    //allocSize = (char*)pDataAligned - (char*)pData; 

    m_Top += size;// +allocSize;

#if ONYX_DEBUG
    memset(pData, 0x00, size);
#endif
    return pData; 
}

void Onyx::Memory::StackAllocator::FreeToMarker(const Marker marker)
{
    assert(marker <= m_Top); 
    m_Top = marker;

#if ONYX_DEBUG
    memset((char*)m_pData + m_Top, 0xcc, marker - m_Top);; 
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
