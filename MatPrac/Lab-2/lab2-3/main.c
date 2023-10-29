#include <stdio.h>
#include "l2-3.h"
#include <malloc.h>

void erase(char_info** info, size_t cnt) {
  char_info** ptr = info;
  for (int i = 0; i < cnt; i++) {
    free(*ptr);
    ptr++;
  }
  free(info);
}

void print(char_info* const* info, size_t cnt) {
  const char_info* const* info_p = info;
  for (int i = 0; i < cnt; i++) {
    char_info const* ptr = *info_p;
    if (ptr == NULL) {
      continue;
    }

    while (ptr->line != -1) {
      printf("substr on %ld line, %ld index\n", ptr->line, ptr->index);
      ptr++;
    }
    info_p++;
    putchar('\n');
  }
}

void print_erase(char_info** info, size_t cnt) {
  print(info, cnt);
  erase(info, cnt);
}

int main() {
  char_info** indexes_arr;
  if (find_all_substr_in_multiple_files(&indexes_arr, 3, "sv", "test.txt", "../test.txt", "test2.txt") != find_ok) {
    printf("something went wrong\n");
  } else {
    print_erase(indexes_arr, 3);
    indexes_arr = NULL;
  }
  return 0;
}
