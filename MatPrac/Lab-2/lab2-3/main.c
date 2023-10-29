#include <stdio.h>
#include "l2-3.h"
#include <malloc.h>

void erase(char_info** info) {
  char_info** ptr = info;
  do {
    free(*ptr);
    ptr++;
  } while (*ptr != NULL);
  free(info);
}

void print(char_info* const* info, size_t cnt) {
  const char_info* const* info_p = info;
  for (int i = 0; i < cnt; i++) {
    char_info const* ptr = *info_p;
    if(ptr == NULL) {
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

int main() {
  char_info** indexes_arr;
  if (find_all_substr_in_multiple_files(&indexes_arr, 2, "sv", "test.txt", "test2.txt") != find_ok) {
    printf("something went wrong\n");
  } else {
    print(indexes_arr, 2);
    erase(indexes_arr);
    indexes_arr = NULL;
  }
  return 0;
}
