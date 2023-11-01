#ifndef MY_FL_L
#define MY_FL_L

#include <stdbool.h>
#include <stdio.h>

void strcpy_without_first(const char cpy[], char var[]);

bool if_flag(const char arg[]);
bool if_ll(const char arg[]);
bool if_i(const char arg[]);
bool if_l(const char arg[]);
bool if_lf(const char arg[]);
bool if_u(const char arg[]);

int my_fgets(FILE* stream, char* buff, unsigned int cap);

int close_files(int count, ...);
#endif