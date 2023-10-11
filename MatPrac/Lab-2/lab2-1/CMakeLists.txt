cmake_minimum_required(VERSION 3.25)
project(lab2_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab2_1 main.c l2-1.h l2-1.c ../../../my_flag_lib.h ../../../my_flag_lib.c)
