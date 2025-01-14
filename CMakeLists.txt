cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")

set(executable_srcs
    src/main.cpp
)

add_executable(executable ${executable_srcs})
