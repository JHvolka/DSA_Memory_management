cmake_minimum_required(VERSION 3.16)
project(Memory_management C)

set(CMAKE_C_STANDARD 99)

add_executable(Memory_management main.c src/BFMM.c src/BFMM.h)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(Memory_management PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(Memory_management PUBLIC DEBUG=0)
endif()