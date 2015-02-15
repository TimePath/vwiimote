cmake_minimum_required(VERSION 2.8.4)
project(wii)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra -pedantic -Wno-unused-parameter -Wno-unknown-pragmas")

set(SOURCE_FILES
    src/main.cpp
    src/bluetooth.cpp
    src/parser.cpp
    src/transport.cpp
)
add_executable(wii ${SOURCE_FILES})
target_link_libraries(wii "bluetooth")
