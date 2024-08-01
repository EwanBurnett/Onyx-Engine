project("Onyx-Engine")

message(STATUS "Building Onyx Engine v${ONYX_VERSION_MAJOR}.${ONYX_VERSION_MINOR}.${ONYX_VERSION_ISSUE} [${GIT_HASH}]")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Version.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Version.cpp" @ONLY)

find_package(Threads REQUIRED)

add_library(${PROJECT_NAME} STATIC "src/Onyx.cpp" "src/Core/Version.cpp" "include/Onyx/Core/Logger.h" "src/Core/Logger.cpp" "include/Onyx/Core/Utility.h" "src/Core/Utility.cpp" "include/Onyx/Core/CVar.h" "src/Core/CVar.cpp" "include/Onyx/Core/Random.h" "src/Core/Random.cpp" "include/Onyx/Core/Timer.h" "src/Core/Timer.cpp" "include/Onyx/Maths/Quaternion.h" "src/Maths/Quaternion.cpp" "include/Onyx/Memory/StackAllocator.h" "src/Memory/StackAllocator.cpp" "include/Onyx/Memory/Memory.h" "include/Onyx/Memory/PoolAllocator.h" "src/Memory/PoolAllocator.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

set(ONYX_ENGINE_COMPILE_DEFINITIONS )

if(ONYX_PLATFORM_LINUX)
    set(ONYX_ENGINE_COMPILE_DEFINITIONS ${ONYX_ENGINE_COMPILE_DEFINITIONS} ONYX_PLATFORM_LINUX=1)
elseif(ONYX_PLATFORM_WINDOWS)
    set(ONYX_ENGINE_COMPILE_DEFINITIONS ${ONYX_ENGINE_COMPILE_DEFINITIONS} ONYX_PLATFORM_WINDOWS=1)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC ${ONYX_ENGINE_COMPILE_DEFINITIONS})
target_link_libraries(${PROJECT_NAME} Threads::Threads)
