cmake_minimum_required(VERSION 3.12)

project(printout)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(printout
        src/main.cpp
        src/options.cpp
        src/printout.cpp
)
