# Build the Engine 
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Engine")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Editor")

# Conditionally build Sample projects.
if(ONYX_BUILD_SAMPLES)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Samples")
endif()

# Conditionally build the Development Testbed project
if(ONYX_BUILD_TESTBED)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Testbed")
endif()

# Conditionally build the Unit Test project
if(ONYX_BUILD_TESTS)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Tests")
endif()