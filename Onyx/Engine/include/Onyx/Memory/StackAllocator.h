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
            ~StackAllocator();

            /**
             * @brief 
             * @param bytes 
             * @param alignment 
             * @return 
            */
            void* Alloc(const uint64_t bytes, const uint64_t alignment = DEFAULT_ALIGNMENT);

            /**
             * @brief 
             * @tparam T 
             * @tparam ...Params 
             * @param count 
             * @param alignment 
             * @param ...params 
             * @return 
            */
            template<typename T, typename ... Params> 
            inline T* Alloc(const uint64_t count, const uint64_t alignment = DEFAULT_ALIGNMENT, Params... params) {
                T* pData = reinterpret_cast<T*>(Alloc(sizeof(T) * count, alignment)); 
                for (uint64_t i = 0; i < count; i++) {
                    new (pData + i) T(params...);
                }
                return pData; 
            }

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
