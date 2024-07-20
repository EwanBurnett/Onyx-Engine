project("Onyx-Tests")

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)

if(ONYX_PLATFORM_WINDOWS)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME} main.cpp "maths.cpp")

target_link_libraries(${PROJECT_NAME} GTest::gtest Onyx-Engine)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})