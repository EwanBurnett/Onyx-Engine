#ifndef ONYX_MEMORY_STACK_ALLOCATOR_H
#define ONYX_MEMORY_STACK_ALLOCATOR_H
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
        class StackAllocator {
        public:
            typedef uint64_t Marker;

            /**
             * @brief
             * @param pData
             * @param capacityBytes
             * @param alignment
            */
            explicit StackAllocator(void* pData, const uint64_t capacityBytes, const uint64_t alignment = DEFAULT_ALIGNMENT);

            /**
             * @brief
             * @param capacityBytes
             * @param alignment
            */
            explicit StackAllocator(const uint64_t capacityBytes, const uint64_t alignment = DEFAULT_ALIGNMENT);

            StackAllocator(const StackAllocator& other);
            StackAllocator(StackAllocator&& other) noexcept;
            ~StackAllocator();

            /**
             * @brief
             * @param bytes
             * @param alignment
             * @return
            */
            void* Alloc(const uint64_t bytes, const uint64_t alignment = DEFAULT_ALIGNMENT);


            /* Ill-formed function - Constructs elements but does not allow for implicit destruction, leading to obscufated issues. 
            * 
            template<typename T, typename ... Args>
            T* Alloc(const uint64_t count, const uint64_t alignment = DEFAULT_ALIGNMENT, Args... args) {
                T* pData = reinterpret_cast<T*>(Alloc(sizeof(T) * count, alignment));

                //Construct each element in place
                for (uint64_t i = 0; i < count; i++) {
                    new(pData + i) T{args...};
                }

                return pData;
            }
            */

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
            void* m_pData;
            Marker m_Top;
            uint64_t m_Capacity;
            bool m_bInPlace;
        };
    }
}

#endif
