#ifndef ONYX_MEMORY_POOL_ALLOCATOR_H
#define ONYX_MEMORY_POOL_ALLOCATOR_H
/**
* @file StackAllocator.h
* @brief Stack Allocator
*
* ------------------------------------------
* @author Ewan Burnett(EwanBurnettSK@Outlook.com)
* @date 2024 - 08 - 01
*/
#include "Memory.h"
#include <cstdint> 

namespace Onyx {
    namespace Memory {
        class PoolAllocator {
        private:
            struct Chunk {
                Chunk* pNext;
            };

        public: 
            explicit PoolAllocator(void* pData, const uint64_t chunkSize, const uint64_t numChunks, const uint64_t alignment = DEFAULT_ALIGNMENT);
            explicit PoolAllocator(const uint64_t chunkSize, const uint64_t numChunks, const uint64_t alignment = DEFAULT_ALIGNMENT);

            ~PoolAllocator(); 

            void* Alloc(); 
            void Free(void* pChunk);

            uint64_t Size() const; 
            uint64_t NumAllocated() const; 

        private:
            uint64_t m_TotalChunks; 
            uint64_t m_AllocatedChunks; 
            Chunk* m_pAlloc; 
            Chunk* m_pBegin; 
            bool m_bIsInPlace; 


        };
    }
}

#endif