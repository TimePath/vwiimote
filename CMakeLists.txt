cmake_minimum_required(VERSION 2.8.4)
project(wii)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra -pedantic -Wno-unused-parameter -Wno-unknown-pragmas")

set(SOURCE_FILES
    main.cpp
    parser.cpp
    transport.cpp
)
add_executable(wii ${SOURCE_FILES})
