cmake_minimum_required(VERSION 2.8.4)
project(vwiimote)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra -pedantic -Wno-unused-parameter -Wno-unknown-pragmas")

Include(ExternalProject)

set(PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR})

ExternalProject_Add(cereal
    PREFIX ${PREFIX}
    GIT_REPOSITORY https://github.com/USCiLab/cereal.git
    INSTALL_COMMAND ""
)
set(cereal_INCLUDE_DIRS "${PREFIX}/src/cereal/include")

set(SOURCE_FILES
    src/main.cpp
    src/bluetooth.cpp
    src/config.cpp
    src/parser.cpp
    src/transport.cpp
)

add_executable(vwiimote ${SOURCE_FILES})
target_include_directories(vwiimote PUBLIC ${cereal_INCLUDE_DIRS})
target_link_libraries(vwiimote "bluetooth")
add_dependencies(vwiimote cereal)
