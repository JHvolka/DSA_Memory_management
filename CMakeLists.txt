cmake_minimum_required(VERSION 3.16)
project(Memory_management C)

set(CMAKE_C_STANDARD 99)

add_executable(Memory_management main.c BFMM.c BFMM.h)