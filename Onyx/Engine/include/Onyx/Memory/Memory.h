#ifndef ONYX_MEMORY_MEMORY_H
#define ONYX_MEMORY_MEMORY_H

#include <cstdint>
#include <assert.h>
#include <cstring>

namespace Onyx {
    namespace Memory {
        
        constexpr uint64_t DEFAULT_ALIGNMENT = 0x40; 

        constexpr inline uint64_t BYTES(const uint64_t numBytes) {
            return numBytes; 
        }
        constexpr inline uint64_t KILOBYTES(const uint64_t numBytes) {
            return numBytes * 1024;
        }

        constexpr inline uint64_t MEGABYTES(const uint64_t numBytes) {
            return numBytes * 1024 * 1024;
        }

        constexpr inline uint64_t GIGABYTES(const uint64_t numBytes) {
            return numBytes * 1024 * 1024 * 1024;
        }

        constexpr inline uintptr_t AlignAddress(uintptr_t address, uint64_t alignment) {
            const uint64_t mask = alignment - 1; 
            assert((alignment & mask) == 0);    //Power of Two
            return ((address + mask) & ~mask);
        }

        template<typename T>
        constexpr inline char* AlignPointer(T* ptr, uint64_t alignment) {
            const uintptr_t address = reinterpret_cast<uintptr_t>(ptr); 
            const uintptr_t alignedAddress = AlignAddress(address, alignment); 
            return reinterpret_cast<T*>(alignedAddress); 
        }

        inline void* AllocAligned(uint64_t bytes, uint64_t alignment) {
            uint64_t worstCaseBytes = bytes + alignment - 1; 

            char* pMem = new char[worstCaseBytes];

            char* pAligned = AlignPointer(pMem, alignment); 
            if (pAligned == pMem) {
                pAligned += alignment;  
            }
#if ONYX_DEBUG
            memset(pMem, 0xff, static_cast<uint64_t>(pAligned - pMem)); 
#endif

            ptrdiff_t shift = pAligned - pMem;
            assert(shift > 0 && shift <= 256);

            pAligned[-1] = static_cast<char>(shift & 0xff); 

            return pAligned;
        }

        inline void FreeAligned(void* pMemory) {
            if (pMemory) {
                //Convert to a char*
                char* pAligned = reinterpret_cast<char*>(pMemory); 

                //Extract the shift
                ptrdiff_t shift = pAligned[-1]; 
                if (shift == 0) {
                    shift = 256; 
                }

                //Delete the actual allocated address
                char* pRawMemory = pAligned - shift; 
                delete[] pRawMemory; 
            }
        }
    }
}

#endif