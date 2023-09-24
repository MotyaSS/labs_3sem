cmake_minimum_required(VERSION 3.25)
project(lab1_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab1_1 main.c l1-1.c ../my_flag_lib.c ../my_flag_lib.h)
