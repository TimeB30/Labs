cmake_minimum_required(VERSION 3.26)
project(lab_3_9 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab_3_9 main.c
        functions.c
        functions.h
        tree.c
        tree.h
        queue.c
        queue.h)

#target_link_libraries(lab_3_9 m)