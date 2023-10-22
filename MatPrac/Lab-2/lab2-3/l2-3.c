#include <string.h>
#include "l2-3.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

int find_all_substr_in_multiple_files(int count, const char* substr, ...) {
  va_list a;
  if (count == 0) {
    return 1;
  }

  va_start(a, substr);
  for (int i = 0; i < count; i++) {
    char* filename = va_arg(a, char*);
    char_info* indexes;
    int rv = find_all_substr(substr, filename, &indexes);
    if (rv != 0) {
      printf("went wrong with %s file\n", filename);
    } else {
      char_info* ptr = indexes;
      printf("for file %s and \'%s\' string:\n", filename, substr);
      while (ptr->line != -1) {
        printf("  substr on %ld line, %ld index\n", ptr->line, ptr->index);
        ptr++;
      }

      free(indexes);
    }
  }
  va_end(a);
  return 0;
}

int find_all_substr(const char* str, const char* filename, char_info** substr_indexes) {
  FILE* stream = fopen(filename, "r");
  if (stream == NULL) {
    return -1;
  }
  *substr_indexes = (char_info*) malloc(sizeof(char_info));
  if (*substr_indexes == NULL) {
    return -2;
  }

  size_t size = 1;
  char_info res_index, cur_index = {.index = -1, .line = 1};
  int rv;
  while ((rv = find_substr_in_file(&res_index, str, stream, &cur_index)) == find_ok) {
    char_info* temp;
    (*substr_indexes)[size - 1] = res_index;
    temp = (char_info*) realloc(*substr_indexes, (++size) * sizeof(char_info));
    if (temp == NULL) {
      free(*substr_indexes);
      substr_indexes = NULL;
      return -2;
    }
    *substr_indexes = temp;
  }
  if (rv == find_not_ok) {
    free(*substr_indexes);
    *substr_indexes = NULL;
    return -2;
  }
  (*substr_indexes)[size - 1].line = -1;
  fclose(stream);
  return 0;
}

bool is_equal_s(const char* s1, const char* s2) {
  while (*s1 != '\0' && *s2 != '\0') {
    if (*s1 != *s2) {
      return false;
    }
    s1++;
    s2++;
  }
  if (*s1 != '\0' || *s2 != '\0') {
    return false;
  }
  return true;
}

int find_substr_in_file(char_info* info, const char* str, FILE* stream, char_info* ptr_pos) {

  size_t len = strlen(str);
  char* strbuf = (char*) malloc(sizeof(char) * (len + 1));
  if (strbuf == NULL) {
    return find_not_ok;
  }
  strbuf[len] = '\0';
  size_t cnt;
  while ((cnt = fread(strbuf, sizeof(char), len, stream)) == len) {
    fseek(stream, 1 - len, SEEK_CUR);
    ptr_pos->index++;
    if (is_equal_s(str, strbuf)) {
      info->index = ptr_pos->index;
      info->line = ptr_pos->line;
      if (*strbuf == '\n') {
        ptr_pos->line++;
        ptr_pos->index = -1;
      }
      return find_ok;
    }
    if (*strbuf == '\n') {
      ptr_pos->line++;
      ptr_pos->index = -1;
    }
  }
  return find_eof;
}