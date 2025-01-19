cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)
project(compress0r)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")

set(executable_srcs
    src/main.cpp
)

enable_testing()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    add_subdirectory(test)
endif()

add_executable(${PROJECT_NAME} ${executable_srcs})

