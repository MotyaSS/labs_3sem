#ifndef L1_1_H
#define L1_1_H

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

HANDLER h_fl_handle(long long number);

int multiples(int arr[], int* len, long long number);

HANDLER p_fl_handle(long long number);

int is_prime(long long number);

HANDLER s_fl_handle(long long number);

int string_separate(char* buff, int* len, int number);

HANDLER e_fl_handle(long long number);

int exp_table(int buff[10][10], long long number);

HANDLER a_fl_handle(long long number);

long long int sum_to_n(long long number);

HANDLER f_fl_handle(long long number);

int factorial(long long number);

#endif