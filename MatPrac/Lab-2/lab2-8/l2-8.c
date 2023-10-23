#include "l2-8.h"
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

bool is_num_valid(const char* str, int base) {
  if (*str == '\0') {
    return false;
  }

  while (*str != '\0') {
    int ch = isdigit(*str) ? *str - '0' : (isalpha(*str) ? tolower(*str) - 'a' + 10 : -1);
    if (ch == -1 || (ch >= base)) {
      return false;
    }
    str++;
  }
  return true;
}

const char* skip_leading_zeros(const char* num) {
  if (*num == '\0') {
    return num;
  }
  while (*num == '0') {
    num++;
  }

  if (*num == '\0') {
    return (num - 1);
  }
  return num;
}

int shift_str_for_i(char* str, unsigned int i) {
  if (i == 0) {
    return 1;
  }

  size_t len = strlen(str);
  for (int j = len; j >= 0; j--) {
    str[j + i] = str[j];
  }
  for (int j = 0; j < i; j++) {
    str[j] = '0';
  }
  return 0;
}

unsigned char int_to_ascii(int a) {
  unsigned char num = a < 10 ? a + '0' : a - 10 + 'A';
  return num;
}

int ascii_to_int(char a) {
  int num = isdigit(a) ? a - '0' : (isalpha(a) ? tolower(a) - 'a' + 10 : -1);
  if (num == -1) {
    return -1;
  }
  return num;
}

sum_st_code sum_up(int base, char** res, size_t* res_size, const char* num) {
  if (base < 2 || base > 36) {
    return sum_base_inv;
  }
  if (!is_num_valid(num, base)) {
    return sum_num_inv;
  }

  size_t len1 = strlen(*res);
  num = skip_leading_zeros(num);
  size_t len2 = strlen(num);
  //num по размеру больше чем res

  if (len2 > len1) {
    while (len2 > *res_size) {
      size_t new_sz = len2 * 2;
      char* temp_p = realloc(*res, new_sz);
      if (temp_p == NULL) {
        return sum_bad_alloc;
      }
      *res = temp_p;
      *res_size = new_sz;
    }
    //добавили нулей, сровняли по размеру
    shift_str_for_i(*res, len2 - len1);
    len1 = strlen(*res);
  }

  bool if_plus_one = false;
  long long cntr = 0;
  //суммируем с конца

  while (cntr < len2) {
    int n1 = ascii_to_int((*res)[(len1 - 1) - cntr]);
    int n2 = ascii_to_int(num[(len2 - 1) - cntr]);
    int sum = n1 + n2;
    if (if_plus_one) {
      sum += 1;
      if_plus_one = false;
    }
    if (sum >= base) {
      if_plus_one = true;
      sum -= base;
    }
    (*res)[(len1 - 1) - cntr] = int_to_ascii(sum);

    cntr++;
  }

  //num закончился, добиваем переносимую еденичку
  while (if_plus_one) {
    if (cntr == len1) {
      if (len1 >= *res_size) {
        size_t new_sz = *res_size + 1;
        char* temp_p = realloc(*res, new_sz);
        if (temp_p == NULL) {
          return sum_bad_alloc;
        }

        *res = temp_p;
        *res_size = new_sz;
      }
      shift_str_for_i(*res, 1);
      len1 += 1;
    }

    int sum = ascii_to_int((*res)[(len1 - 1) - cntr]) + 1;

    if_plus_one = false;
    if (sum >= base) {
      if_plus_one = true;
      sum -= base;
    }
    (*res)[(len1 - 1) - cntr] = int_to_ascii(sum);
    cntr++;
  }

  return sum_ok;
}

sum_st_code sum_base_n(size_t cnt, int base, char** res, ...) {
  if (cnt == 0) {
    return sum_cnt_inv;
  }
  if (base < 2 || base > 36) {
    return sum_base_inv;
  }

  va_list a;
  size_t size = 1024;
  char* sum_res = malloc(size * sizeof(char));
  if (sum_res == NULL) {
    return sum_bad_alloc;
  }
  strcpy(sum_res, "0");
  va_start(a, res);
  for (int i = 0; i < cnt; i++) {
    char* t_num = va_arg(a, char*);
    switch (sum_up(base, &sum_res, &size, t_num)) {
      case sum_bad_alloc:
        free(sum_res);
        return sum_bad_alloc;
      case sum_num_inv:
        printf("%s is invalid\n", t_num);
        break;
      default:
        break;
    }
  }
  res = &sum_res;
  printf("sum result is - %s\n", sum_res);
  va_end(a);
  return sum_ok;
}