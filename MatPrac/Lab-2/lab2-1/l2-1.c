#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "l2-1.h"
#include "../../../my_flag_lib.h"

st_code flag_compare(int argc, char* argv[]);

st_code l_fl(int argc, char* argv[]);
st_code r_fl(int argc, char* argv[]);
st_code u_fl(int argc, char* argv[]);
st_code n_fl(int argc, char* argv[]);
st_code c_fl(int argc, char* argv[]);

st_code input(int argc, char* argv[]) {
  if (argc <= 2) {
    return inv_argc;
  }
  if (!if_flag(argv[1])) {
    return inv_flag;
  }

  return flag_compare(argc, argv);
}

st_code flag_compare(int argc, char* argv[]) {
  char* flag = argv[1] + 1;
  if (flag[0] == 0 || flag[1] != 0) {
    return unknown_flag;
  }
  switch (*flag) {
    case 'l':
      return l_fl(argc, argv);
    case 'r':
      return r_fl(argc, argv);
    case 'u':
      return u_fl(argc, argv);
    case 'n':
      return n_fl(argc, argv);
    case 'c':
      return c_fl(argc, argv);
  }
  return unknown_flag;
}

st_code l_fl(int argc, char* argv[]) {
  if (argc != 3) {
    return inv_argc;
  }

  printf("length: %lld\n", str_length(argv[2]));
  return ok;
}

st_code r_fl(int argc, char* argv[]) {
  if (argc != 3) {
    return inv_argc;
  }
  char* string = (char*) malloc(sizeof(char) * (str_length(argv[2]) + 1));
  if (string == NULL) {
    return not_enough_space;
  }
  str_reverse(argv[2], string);
  printf("reversed string: %s\n", string);
  free(string);
  return ok;
}

st_code u_fl(int argc, char* argv[]) {
  if (argc != 3) {
    return inv_argc;
  }
  char* string = (char*) malloc(sizeof(char) * (str_length(argv[2]) + 1));
  if (string == NULL) {
    return not_enough_space;
  }
  str_odd_element_toupper(argv[2], string);
  printf("formatted string: %s\n", string);
  free(string);
  return ok;
}

st_code n_fl(int argc, char* argv[]) {
  if (argc != 3) {
    return inv_argc;
  }
  char* string = (char*) malloc(sizeof(char) * (str_length(argv[2]) + 1));
  if (string == NULL) {
    return not_enough_space;
  }
  str__num_alph_other__order(argv[2], string);
  printf("formatted string: %s\n", string);
  free(string);
  return ok;
}

st_code c_fl(int argc, char* argv[]) {
  if (argc <= 3) {
    return inv_argc;
  }

  if (!if_i(argv[2])) {
    return inv_num;
  }
  int seed = strtol(argv[2], NULL, 10);
  ull size = 0;
  for (int i = 3; i < argc; i++) {
    size += str_length(argv[i]);
  }
  char* string = (char*) malloc(sizeof(char) * (size + 1));
  if (string == NULL) {
    return not_enough_space;
  }

  if(cat_string_rand_order(seed, argv + 3, argc - 3, string) == 0) {
    printf("random ordered string: %s\n", string);
  }

  free(string);
  return ok;
}

ull str_length(const char* str) {
  if (str == NULL) {
    return 0;
  }
  ull size = 0;
  for (; str[size] != 0; size++);
  return size;
}

int str_reverse(const char* src, char* dest) {
  if (src == NULL || dest == NULL) {
    return -1;
  }

  ull len = str_length(src);
  for (int i = 0; i <= len / 2; i++) {
    dest[i] = src[len - 1 - i];
    dest[len - 1 - i] = src[i];
  }
  dest[len] = '\0';
  return 0;
}

int str_odd_element_toupper(const char* src, char* dest) {
  if (src == NULL || dest == NULL) {
    return -1;
  }
  ull i = 0;
  for (; src[i] != '\0'; i++) {
    if (i & 1) {
      dest[i] = toupper(src[i]);
    } else {
      dest[i] = src[i];
    }
  }
  dest[i] = '\0';
  return 0;
}

int str__num_alph_other__order(const char* src, char* dest) {
  if (src == NULL || dest == NULL) {
    return -1;
  }
  int ind = 0;
  for (int i = 0; src[i] != '\0'; i++) {
    if (isdigit(src[i])) {
      dest[ind++] = src[i];
    }
  }
  for (int i = 0; src[i] != '\0'; i++) {
    if (isalpha(src[i])) {
      dest[ind++] = src[i];
    }
  }
  for (int i = 0; src[i] != '\0'; i++) {
    if (!isalnum(src[i])) {
      dest[ind++] = src[i];
    }
  }
  dest[ind] = '\0';
  return 0;
}

char* str_cpy(const char* src, char* dest) {
  int i = 0;
  for (; src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest + i;
}

int rand_comp(const void* i, const void* j) {
  return rand() % 2 ? 1 : -1;
}

int cat_string_rand_order(int seed, char* strings_arr[], int str_cnt, char* dest) {
  srand(seed);
  char** arr = (char**) malloc(sizeof(char*) * str_cnt);
  if (arr == NULL) {
    return -1;
  }
  for (int i = 0; i < str_cnt; i++) {
    arr[i] = strings_arr[i];
  }

  qsort(arr, str_cnt, sizeof(char*), rand_comp);
  *dest = '\0';
  char* ptr = dest;
  for (int i = 0; i < str_cnt; i++) {
    ptr = str_cpy(arr[i], ptr);
  }
  free(arr);
  return 0;
}