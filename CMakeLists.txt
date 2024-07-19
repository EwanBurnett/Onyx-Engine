cmake_minimum_required(VERSION 3.14)
project("Onyx" VERSION 0.0.1)

# Options
option(ONYX_BUILD_TESTS "Build the Unit Test project" OFF)
option(ONYX_BUILD_TESTBED "Build the Development Test Project" OFF)
option(ONYX_BUILD_SAMPLES "Build Sample Projects" ON)
option(ONYX_BUILD_DOCS "Generate Local Doxygen Documentation (Requires Doxygen!)" OFF)

# Versioning
set(ONYX_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR})
set(ONYX_VERSION_MINOR ${CMAKE_PROJECT_VERSION_MINOR})
set(ONYX_VERSION_ISSUE ${CMAKE_PROJECT_VERSION_PATCH})

include("${CMAKE_SOURCE_DIR}/CMake/CheckGitHash.cmake")

# Platform Information
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Platform \'Linux\' Detected.")
    set(ONYX_PLATFORM_LINUX 1)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(ONYX_PLATFORM_WINDOWS 1)
    message(STATUS "Platform \'Windows\' Detected.")
else()
    message(FATAL_ERROR "Unknown Platform \'${CMAKE_SYSTEM_NAME}\'Detected!")
endif()

# Configuration
add_compile_definitions($<$<CONFIG:DEBUG>:ONYX_DEBUG>)  # Define ONYX_DEBUG for debug configurations. 

file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/lib") # Library output directory
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/bin") # Binary output directory

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/)

set(CMAKE_DEBUG_POSTFIX "d") 

# Build the Engine
add_subdirectory("${CMAKE_SOURCE_DIR}/Onyx/")
add_subdirectory("${CMAKE_SOURCE_DIR}/Tests/")
add_subdirectory("${CMAKE_SOURCE_DIR}/Tools/")
if(ONYX_BUILD_TESTBED)
    add_subdirectory("${CMAKE_SOURCE_DIR}/Testbed/")
endif()
add_subdirectory("${CMAKE_SOURCE_DIR}/Samples/")


# add_custom_target(UpdateVersionHash COMMAND ${CMAKE_COMMAND} -Dpre_configure_dir=${pre_configure_dir} -Dpost_configure_file=${post_configure_dir} -P "${CMAKE_SOURCE_DIR}/CMake/CheckGitHash.cmake" BYPRODUCTS ${post_configure_file})

# Optionally generate Documentation files
if(ONYX_BUILD_DOCS)
    find_package(Doxygen QUIET)
    if(DOXYGEN_FOUND)
        message(STATUS "Generating Doxygen Documentation.")
        if(EXISTS "${CMAKE_SOURCE_DIR}/Doxyfile")
            execute_process(COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_SOURCE_DIR}/Doxyfile" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} RESULT_VARIABLE DOCUMENTATION_GENERATION_RESULT)
            if(NOT DOCUMENTATION_GENERATION_RESULT EQUAL "0")
                message(SEND_ERROR "Doxygen Generation failed with status ${DOCUMENTATION_GENERATION_RESULT}!")
            endif()
        else()
            message(SEND_ERROR "Doxyfile not found!")
        endif()
    else()
        message(SEND_ERROR "Failed to find Doxygen installation!")
    endif()
endif()
