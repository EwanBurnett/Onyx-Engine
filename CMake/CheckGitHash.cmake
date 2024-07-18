# Retrieves a git commit hash
# https://jonathanhamberg.com/post/cmake-embedding-git-hash/

message(STATUS "Retrieving Git Commit hash.")

find_package(Git REQUIRED)
if(GIT_FOUND)
    execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --format=%h WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} OUTPUT_VARIABLE GIT_HASH OUTPUT_STRIP_TRAILING_WHITESPACE)    
    message(STATUS "Git Commit Hash = 0x${GIT_HASH}")
else()
    message(SEND_ERROR "Git Installation not found!")
endif()
