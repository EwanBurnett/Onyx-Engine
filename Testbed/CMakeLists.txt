project("Testbed")
message(STATUS "Building Testbed Application.")

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Onyx-Engine)
