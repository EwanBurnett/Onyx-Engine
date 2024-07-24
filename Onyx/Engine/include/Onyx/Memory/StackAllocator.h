#ifndef ONYX_MEMORY_STACK_ALLOCATOR_H
#define ONYX_MEMORY_STACK_ALLOCATOR_H
#include "Memory.h"
#include <cstdint> 

namespace Onyx {
    namespace Memory {
        class StackAllocator {
        public:
            typedef uint64_t Marker;

            /**
             * @brief 
             * @param pData 
             * @param capacity 
             * @param alignment 
            */
            explicit StackAllocator(void* pData, const uint64_t capacity, const uint64_t alignment = DEFAULT_ALIGNMENT);

            /**
             * @brief 
             * @param capacity 
             * @param alignment 
            */
            explicit StackAllocator(const uint64_t capacity, const uint64_t alignment = DEFAULT_ALIGNMENT);
            ~StackAllocator();

            /**
             * @brief 
             * @param size 
             * @param alignment 
             * @return 
            */
            void* Alloc(const uint64_t size, const uint64_t alignment = DEFAULT_ALIGNMENT);

            /**
             * @brief 
             * @param marker 
            */
            void FreeToMarker(const Marker marker);

            /**
             * @brief 
             * @return 
            */
            Marker Top() const;

            /**
             * @brief 
             * @return 
            */
            uint64_t Capacity() const;

            /**
             * @brief 
             * @return 
            */
            uint64_t BytesAllocated() const;

            /**
             * @brief 
            */
            void Clear();

        private:
            uint64_t m_Alignment;
            void* m_pData;
            Marker m_Top;
            uint64_t m_Capacity;
        };
    }
}

#endif
