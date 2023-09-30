#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "l1-1.h"
#include "..\my_flag_lib.h"

#define BUFF_SIZE 100

HANDLER my_func(int argc, char* argv[]) {
  if (argc != 3) {
    return ARGUMENTS_COUNT_IR;
  }
  if (!if_flag(argv[1]) || strlen(argv[1]) >= BUFF_SIZE) {
    return FLAG_ISSUE;
  }
  char flag[BUFF_SIZE];
  strcpy_without_first(argv[1], flag);
  if (!if_ll(argv[2])) {
    return NOT_NUMBER;
  }
  long long number = strtoll(argv[2], NULL, 10);
  int code = flag_sw_case(flag, number);

  return code;
}

int h_fl_handle(const long long number) {
  long long n_temp = number < 0 ? -number : number;

  if (n_temp > 100 || n_temp == 0) {
    return H_NO_SUCH_NUMBERS;
  }
  int buff[BUFF_SIZE];
  int len = 0;
  multiples(buff, &len, n_temp);

  for (int i = 0; i < len; i++) {
    printf("%d ", buff[i]);
  }
  printf("\n");
  return OK;
}

int p_fl_handle(const long long number) {
  if (is_prime(number)) {
    printf("Prime\n");
  }
  else {
    printf("Complex\n");
  }
  return OK;
}

int s_fl_handle(const long long number) {
  char buff[BUFF_SIZE];
  int len = 0;
  string_separate(buff, &len, number);

  printf("%s\n", buff);
  return OK;
}

int e_fl_handle(const long long number) {
  if (number > 10) {
    return E_MORE_THAN_TEN;
  }
  if (number <= 0) {
    return E_NON_POSITIVE;
  }
  int arr[10][10];
  exp_table(arr, number);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < number; j++) {
      int x = i + 1, y = j + 1;
      printf("%d ^ %d = %d\n", x, y, arr[i][j]);
    }
    printf("\n");
  }
  return OK;
}

int a_fl_handle(const long long number) {
  long long ans = sum_to_n(number);
  if (number <= 0) {
    return A_NEGATIVE;
  }
  if (ans == A_MORE_THAN_LLMAX) {
    return A_MORE_THAN_LLMAX;
  }
  printf("%lld\n", ans);
  return OK;
}


int f_fl_handle(const long long number) {
  long long ans = factorial(number);
  if (ans == F_MORE_THAN_LLMAX) {
    return F_MORE_THAN_LLMAX;
  }
  printf("%lld\n", ans);
  return OK;
}

int flag_sw_case(const char* flag, const long long number) {
  if(strlen(flag) != 1)
    return FLAG_UNDEF;
  switch(flag[0]){
    case 'h':
      return h_fl_handle(number);
    case 'p':
      return p_fl_handle(number);
    case 's':
      return s_fl_handle(number);
    case 'e':
      return e_fl_handle(number);
    case 'a':
      return a_fl_handle(number);
    case 'f':
      return f_fl_handle(number);
    default:
      return FLAG_UNDEF;
  }
  /*
  if (strcmp(flag, "h") == 0) {
    return h_fl_handle(number);
  } else if (strcmp(flag, "p") == 0) {
    return p_fl_handle(number);
  } else if (strcmp(flag, "s") == 0) {
    return s_fl_handle(number);
  } else if (strcmp(flag, "e") == 0) {
    return e_fl_handle(number);
  } else if (strcmp(flag, "a") == 0) {
    return a_fl_handle(number);
  } else if (strcmp(flag, "f") == 0) {
    return f_fl_handle(number);
  } else {
    return FLAG_UNDEF;
  }*/
}

int multiples(int* arr, int* len, const long long number) {
  long long n_temp = number;
  for (long long i = n_temp; i < BUFF_SIZE; i += number) {
    arr[(*len)] = i;
    (*len)++;
  }
  return OK;
}

int is_prime(const long long number) {
  long long temp_n = number < 0 ? -number : number;
  double limit = floor(sqrt(temp_n));
  if (number == 1)
    return P_NOT_COMPLEX_OR_PRIME;
  if (number == 2)
    return true;
  if (number % 2 == 0)
    return true;

  for (long long i = 3; i < limit; i += 2) {
    if (temp_n % i == 0)
      return false;
  }
  return true;
}

int string_separate(char* buff, int* len, const int number) {
  bool flag = false;
  int temp_n = number;
  if (number < 0) {
    temp_n *= -1;
    flag = true;
  }
  int ier = 0;
  do {
    if (ier == 1) {
      ier = 0;
      buff[(*len)++] = ' ';
    } else if (ier == 0) {
      ier = 1;

      buff[(*len)++] = temp_n % 10 + '0';
      temp_n /= 10;
    }
  } while (temp_n != 0);

  if (flag) {
    buff[(*len)++] = ' ';
    buff[(*len)++] = '-';
  }

  strrev(buff);
  return OK;
}


int exp_table(int buff[10][10], const long long number) {
  for (int i = 0; i < 10; i++) {
    int x = i + 1;
    for (int j = 0; j < number; j++) {
      buff[i][j] = x;
      x *= (i + 1);
    }
  }
  return OK;
}

long long int sum_to_n(const long long number) {
  if (number <= 0)
    return A_NEGATIVE;
  long long sum = 0;
  for (int i = number; i >= 1; i--) {
    if (sum > LONG_LONG_MAX - i)
      return A_MORE_THAN_LLMAX;
    sum += i;
  }
  return sum;
}

int factorial(const long long number) {
  if (number <= 1)
    return 1;

  long long temp = factorial(number - 1);
  if (temp <= LONG_LONG_MAX / number) {
    return temp * number;
  }
  return F_MORE_THAN_LLMAX;
}

