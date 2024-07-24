#ifndef ONYX_MEMORY_MEMORY_H
#define ONYX_MEMORY_MEMORY_H

#include <cstdint>
#include <assert.h>

namespace Onyx {
    namespace Memory {
        
        constexpr uint64_t DEFAULT_ALIGNMENT = 0x80; 

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
            assert((alignment & mask) == 0); 
            return (address + mask) & ~mask; 
        }
    }
}

#endif