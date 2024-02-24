cmake_minimum_required(VERSION 3.22)
project(CLionProjects C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-lm)
add_library(func SHARED functions.h functions.c)

add_executable(CLionProjects main.c
       
)

target_link_libraries(CLionProjects PRIVATE func)
