project("Onyx-Engine")

message(STATUS "Configuring version v${ONYX_VERSION_MAJOR}.${ONYX_VERSION_MINOR}.${ONYX_VERSION_ISSUE} [${GIT_HASH}]")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/Version.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/Version.cpp" @ONLY)

add_library(${PROJECT_NAME} STATIC "src/Onyx.cpp" "src/Version.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")