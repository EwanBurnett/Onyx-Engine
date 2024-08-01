#include "Onyx/Memory/PoolAllocator.h"
#include "Onyx/Core/Logger.h"

Onyx::Memory::PoolAllocator::PoolAllocator(void* pData, const uint64_t chunkSize, const uint64_t numChunks, const uint64_t alignment)
{
    m_bIsInPlace = true; 
    m_AllocatedChunks = 0; 
    m_TotalChunks = numChunks; 

    //Set up the linked list of chunks
    Chunk* begin = reinterpret_cast<Chunk*>(pData);
    Chunk* chunk = begin; 
    for (uint64_t i = 0; i < numChunks - 1; i++) {
        chunk->pNext = reinterpret_cast<Chunk*>(reinterpret_cast<char*>(chunk) + chunkSize);
        chunk = chunk->pNext;
    }

    chunk->pNext = nullptr; 

    m_pAlloc = begin; 

}

Onyx::Memory::PoolAllocator::PoolAllocator(const uint64_t chunkSize, const uint64_t numChunks, const uint64_t alignment)
{
    m_bIsInPlace = false; 
    m_AllocatedChunks = 0; 
    m_TotalChunks = numChunks; 

    //Allocate the requisite number of chunks
    const uint64_t allocSize = chunkSize * numChunks; 
    void* pData = AllocAligned(allocSize, alignment);

    //Set up the linked list of chunks
    m_pBegin = reinterpret_cast<Chunk*>(pData);
    Chunk* chunk = m_pBegin; 
    for (uint64_t i = 0; i < numChunks - 1; i++) {
        chunk->pNext = reinterpret_cast<Chunk*>(reinterpret_cast<char*>(chunk) + chunkSize);
        chunk = chunk->pNext;
    }

    chunk->pNext = nullptr; 

    m_pAlloc = m_pBegin; 
}

Onyx::Memory::PoolAllocator::~PoolAllocator()
{
    if (!m_bIsInPlace) {
        FreeAligned(m_pBegin); 
    }
}

void* Onyx::Memory::PoolAllocator::Alloc()
{

    Chunk* pChunk = m_pAlloc; 
    if (pChunk == nullptr) {
        Onyx::Log::Fatal(__FILE__, __LINE__, __PRETTY_FUNCTION__, "Unable to allocate pool chunk!\n");
    }
    m_pAlloc = m_pAlloc->pNext; 
    m_AllocatedChunks++; 

    return reinterpret_cast<void*>(pChunk); 
}

void Onyx::Memory::PoolAllocator::Free(void* pChunk)
{
    Chunk* chunk = reinterpret_cast<Chunk*>(pChunk); 
    chunk->pNext = m_pAlloc; 
    m_pAlloc = chunk;
    m_AllocatedChunks--; 
}

uint64_t Onyx::Memory::PoolAllocator::Size() const
{
    return m_TotalChunks;
}

uint64_t Onyx::Memory::PoolAllocator::NumAllocated() const
{
    return m_AllocatedChunks;
}
