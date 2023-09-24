#include <stdbool.h>

#ifndef __L1
#define BUFF_SIZE 100

typedef enum {
  H_NO_SUCH_NUMBERS = 1,
  E_MORE_THAN_TEN,
  E_NON_POSITIVE,
  A_NEGATIVE,
  P_NOT_COMPLEX_OR_PRIME,
  A_MORE_THAN_LLMAX = -1,
  F_MORE_THAN_LLMAX = -2
} HANDLERS;


int flag_sw_case(const char* flag, long long number);

int h_fl_handle(const long long number);

int h_fl(int arr[], int* len, const long long number);

int p_fl_handle(const long long number);

int p_fl(const long long number);

int s_fl_handle(const long long number);

int s_fl(char* buff, int* len, const int number);

int e_fl_handle(const long long number);

int e_fl(int buff[10][10], const long long number);

int a_fl_handle(const long long number);

long long int a_fl(const long long number);

int f_fl_handle(const long long number);

int f_fl(const long long number);

#endif