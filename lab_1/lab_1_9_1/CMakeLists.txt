cmake_minimum_required(VERSION 3.22)
project(lab1 C)
set(CMAKE_C_STANDARD 11)

add_executable(lab1 main.c)

add_library(func SHARED functions.h functions.c)
target_link_libraries(lab1 PRIVATE func)
target_link_libraries(func m)   