#include "my_string.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Construction and destruction

int string_init(String* str, size_t n) {
  str->_buf = (char*) malloc(sizeof(char) * (n + 1));
  *(str->_buf) = 0;
  if (!str->_buf) {
    return -1;
  }
  str->_size = 0;
  str->_cap = n;
  return 0;
}

int string_constr(char const* src, String* dest) {
  size_t len = strlen(src);
  if (string_init(dest, len) != 0) {
    return -1;
  }
  for (int i = 0; i < len; i++) {
    dest->_buf[i] = src[i];
  }
  dest->_buf[len] = 0;
  dest->_size = len;
  return 0;
}

int string_destr(String* str) {
  if (str->_buf == NULL) {
    return -1;
  }
  free(str->_buf);
  str->_buf = NULL;
  str->_cap = -1;
  str->_size = -1;
  return 0;
}

// two strings

int string_is_equal(String const* str1, String const* str2) {
  char* p1 = str1->_buf;
  char* p2 = str2->_buf;
  do {
    if (*p1 != *p2) {
      return 0;
    }
    ++p1;
    ++p2;
  } while (*p1 != 0 && *p2 != 0);
  if (*p1 == *p2) {
    return 1;
  }
  return 0;
}

int str1_cmp_str2(String const* str1, String const* str2) {
  int first_not_equal = 0;
  char* p1 = str1->_buf;
  char* p2 = str2->_buf;
  while (*p1 != 0 && *p2 != 0) {
    if (first_not_equal == 0) {
      first_not_equal = *p1 > *p2 ? 1 : (*p2 > *p1 ? -1 : 0);
    }
    p1++;
    p2++;
  }
  if (*p1 != *p2) {
    return *p1 == 0 ? -1 : 1;
  }
  return first_not_equal;
}

int string_copy(String const* src, String* dest) {
  int i = 0;
  while ((src->_buf[i]) != 0) {
    if (i >= dest->_cap) {
      if (dest->_cap == 0) {
        if (string_resize(dest, 1) != 0) {
          return -1;
        }
      }
      if (string_resize(dest, dest->_cap * 2) != 0) {
        return -1;
      }
    }
    dest->_buf[i] = src->_buf[i];
    i++;
  }
  dest->_buf[i] = 0;
  dest->_size = src->_size;
  return 0;
}

// single string

int get_string(String* str, FILE* stream) {
  str->_size = 0;
  size_t i = 0;
  int ch;
  while ((ch = fgetc(stream)) != EOF && !isspace(ch)) {
    if (i >= str->_size) {
      if (str->_cap == 0) {
        if (string_resize(str, 1) != 0) {
          return get_str_bad_alloc;
        }
      }
      if (string_resize(str, str->_cap * 2) != 0) {
        return get_str_bad_alloc;
      }
    }
    str->_buf[i] = ch;
    i++;
  }
  str->_buf[i] = 0;
  if (i == 0) {
    return get_str_empty;
  }

  return get_str_ok;
}

int string_resize(String* str, size_t n) {
  if (n <= str->_cap) {
    return 1;
  }

  char* temp = (char*) realloc(str->_buf, sizeof(char) * (n + 1));
  if (temp == NULL) {
    return -1;
  }
  str->_buf = temp;
  str->_cap = n;
  return 0;
}

int string_clear(String* str) {
  str->_buf[0] = 0;
  str->_size = 0;
  return 0;
}

void show_string(String const* str) {
  printf("%s\n", str->_buf);
}