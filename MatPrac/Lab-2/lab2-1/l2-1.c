#include <stdio.h>
#include <stdlib.h>
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
  new_str__num_al_other__order(argv[2], string);
  printf("formatted string: %s\n", string);
  free(string);
  return ok;
}

st_code c_fl(int argc, char* argv[]) {
  if (argc <= 3) {
    return inv_argc;
  }

  if (!if_i(argv[1])) {
    return inv_num;
  }
  int seed = strtol(argv[1], NULL, 10);
  ull size = 0;
  for (int i = 3; i < argc; i++) {
    size += str_length(argv[i]);
  }
  char* string = (char*) malloc(sizeof(char) * (size + 1));
  cat_string_rand_order(seed, argv + 3, argc - 4, string);
  printf("random ordered string: %s\n", string);
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
  dest[len] = '\0';
  for (int i = 0; i <= len / 2; i++) {
    dest[i] = src[len - 1 - i];
  }
  return 0;
}

int str_odd_element_toupper(const char* src, char* dest) {

}

int new_str__num_al_other__order(const char* src, char* dest) {

}

int cat_string_rand_order(int seed, char* strings_arr[], int str_cnt, char* dest) {

}