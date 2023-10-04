#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "l1-10.h"

void get_string_safely_realloc(char** string, int* str_capacity, FILE* stream) {
  if (stream == NULL || string == NULL) {
    return;
  }
  int size = 0;
  int a;
  while ((a = getc(stream)) != EOF && a != '\n') {
    (*string)[size++] = (char) a;
    if (size >= *str_capacity) {
      *str_capacity = *str_capacity * 2;
      *string = (char*) realloc(*string, *str_capacity);
      if (string == NULL) {
        perror("PIZDEC VASYAN U NAS PROBLEMS\n");
        return;
      }
    }
  }
  (*string)[size] = '\0';
}

bool if_lowercase_in_string(const char* string) {
  for (int i = 0; string[i] != '\0'; i++) {
    if (string[i] >= 'a' && string[i] <= 'z') {
      return true;
    }
  }
  return false;
}

int input_numbers(char** string, int* cap, long* max_, const int base) {
  char* endptr;
  long num;
  do {
    get_string_safely_realloc(string, cap, stdin);
    if (strcmp(*string, "Stop") == 0) {
      break;
    }
    if (if_lowercase_in_string(*string)) {
      printf("Ignored\n");
      continue;
    }
    num = strtol(*string, &endptr, base);
    if (endptr != *string + strlen(*string)) {
      printf("Ignored\n");
      continue;
    }
    *max_ = abs(num) > *max_ ? num : *max_;
  } while (1);

  return 0;
}

myf_sc find_max_from_input(char** string, int* cap, long* result) {
  printf("Enter base: ");
  get_string_safely_realloc(string, cap, stdin);
  char* endptr;
  long base = strtol(*string, &endptr, 10);
  if (endptr != *string + strlen(*string)) {
    return INCORRECT_STRING;
  }
  if (base < 2 || base > 36) {
    return INVALID_BASE;
  }

  long max_ = 0;
  input_numbers(string, cap, &max_, base);
  *result = max_;
  return OK;
}

void show_number_with_base(long num, const int base) {
  char buff[66];
  buff[65] = 0;
  char* ptr = buff + 64;
  bool if_negative = false;
  if (num < 0) {
    num *= -1;
    if_negative = true;
  }
  while (num > 0) {
    int rem = num % base;
    num /= base;
    if (rem >= 0 && rem <= 9) {
      *ptr = rem + '0';
    } else if (rem >= 10) {
      *ptr = rem + 'A' - 10;
    }
    ptr--;
  }
  if (if_negative) {
    *ptr = '-';
    ptr--;
  }
  ptr++;
  printf("%s\n", ptr);
}