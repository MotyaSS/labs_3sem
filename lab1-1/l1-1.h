#ifndef _L1_1_H_
#define _L1_1_H_

#define BUFF_SIZE 100
#include <stdbool.h>

typedef enum {
  ARGUMENTS_COUNT_IR = -10,
  FLAG_ISSUE,
  NOT_NUMBER,
  OK = 0,
  FLAG_UNDEF,
  H_NO_SUCH_NUMBERS,
  E_MORE_THAN_TEN,
  E_NON_POSITIVE,
  A_NEGATIVE,
  P_NOT_COMPLEX_OR_PRIME,
  A_MORE_THAN_LLMAX = -1,
  F_MORE_THAN_LLMAX = -2
} HANDLER;


int flag_sw_case(const char* flag, long long number);

HANDLER h_fl_handle(const long long number);

int h_fl(int arr[], int* len, const long long number);

HANDLER p_fl_handle(const long long number);

int p_fl(const long long number);

HANDLER s_fl_handle(const long long number);

int s_fl(char* buff, int* len, const int number);

HANDLER e_fl_handle(const long long number);

int e_fl(int buff[10][10], const long long number);

HANDLER a_fl_handle(const long long number);

long long int a_fl(const long long number);

HANDLER f_fl_handle(const long long number);

int f_fl(const long long number);

#endif