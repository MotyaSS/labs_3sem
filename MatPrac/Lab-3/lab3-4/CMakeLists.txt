cmake_minimum_required(VERSION 3.25)
project(lab3_4 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab3_4 main.c my_string.c my_string.h mail.h mail.c mail_bst.c l3-4.c l3-4.h ../../../my_flag_lib.h ../../../my_flag_lib.c)
