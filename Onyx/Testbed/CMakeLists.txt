project("Testbed")
message(STATUS "Building Testbed Application.")

set(TESTBED_SOURCES main.cpp)

if(ONYX_PLATFORM_WINDOWS)
    set(TESTBED_SOURCES ${TESTBED_SOURCES} Resources.rc)
endif()

add_executable(${PROJECT_NAME} ${TESTBED_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Onyx-Engine)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}/"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Resources"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources"
    COMMENT "Copying Application Resources to Output Directory."
)

