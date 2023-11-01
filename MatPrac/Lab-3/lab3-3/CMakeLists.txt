cmake_minimum_required(VERSION 3.25)
project(lab3_3 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab3_3 main.c l3-3.h l3-3.c ../../../my_flag_lib.h ../../../my_flag_lib.c empv.c)
