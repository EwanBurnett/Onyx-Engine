cmake_minimum_required(VERSION 3.14)
project("Onyx" VERSION 0.0.1)

option(ONYX_BUILD_TESTS "Build the Unit Test project" OFF)
option(ONYX_BUILD_TESTBED "Build the Development Test Project" OFF)
option(ONYX_BUILD_SAMPLES "Build Sample Projects" ON)
option(ONYX_BUILD_DOCS "Generate Local Doxygen Documentation (Requires Doxygen!)" OFF)

# Versioning
set(ONYX_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR})
set(ONYX_VERSION_MINOR ${CMAKE_PROJECT_VERSION_MINOR})
set(ONYX_VERSION_ISSUE ${CMAKE_PROJECT_VERSION_PATCH})

include("${CMAKE_SOURCE_DIR}/CMake/CheckGitHash.cmake")


# Build the Engine
add_subdirectory("${CMAKE_SOURCE_DIR}/Onyx/")
add_subdirectory("${CMAKE_SOURCE_DIR}/Tests/")
add_subdirectory("${CMAKE_SOURCE_DIR}/Tools/")
if(ONYX_BUILD_TESTBED)
    add_subdirectory("${CMAKE_SOURCE_DIR}/Testbed/")
endif()
add_subdirectory("${CMAKE_SOURCE_DIR}/Samples/")


# Optionally generate Documentation files
if(ONYX_BUILD_DOCS)
    find_package(Doxygen QUIET)
    if(DOXYGEN_FOUND)
        message(STATUS "Generating Doxygen Documentation.")
        if(EXISTS "${CMAKE_SOURCE_DIR}/Doxyfile")
            execute_process(COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile RESULT_VARIABLE DOCUMENTATION_GENERATION_RESULT)
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
