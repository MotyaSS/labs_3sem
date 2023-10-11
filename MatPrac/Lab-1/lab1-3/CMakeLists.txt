cmake_minimum_required(VERSION 3.25)
project(lab1_3 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab1_3 main.c ../my_flag_lib.c ../my_flag_lib.h l1-3.h l1-3.c)
