#include "l4-7.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../my_flag_lib.h"

//
//                STRING
//

int string_push_back(String* str, char ch) {
  if (str->_size == str->_cap) {
    if (string_resize(str, str->_cap * 2) != 0) {
      return -1;
    }
    str->_cap *= 2;
  }

  str->_buf[str->_size++] = ch;
  str->_buf[str->_size] = 0;
  return 0;
}

int str_vec_init(StringVec* vec, size_t cap) {
  if ((vec->buf = (String*) malloc(sizeof(String) * cap)) == NULL) {
    return -1;
  }
  vec->cap = cap;
  vec->cnt = 0;
  return 0;
}

int str_vec_resize(StringVec* vec, size_t cap) {
  if (cap < vec->cap) {
    return -1;
  }

  String* temp = realloc(vec->buf, sizeof(String) * cap);
  if (temp == NULL) {
    return 1;
  }
  vec->cap = cap;
  vec->buf = temp;
  return 0;
}

int str_vec_clear(StringVec* vec) {
  for (int i = 0; i < vec->cnt; i++) {
    string_destr(&vec->buf[i]);
  }
  vec->cnt = 0;
  return 0;
}

int str_vec_dest(StringVec* vec) {
  str_vec_clear(vec);
  free(vec->buf);
  vec->cap = 0;
  vec->buf = NULL;
  return 0;
}

int str_vec_add(StringVec* vec, String* to_add) {
  if (vec->cap == vec->cnt) {
    if (str_vec_resize(vec, (vec->cap * 2)) != 0) {
      return -1;
    }
    vec->cap *= 2;
  }
  vec->buf[vec->cnt++] = *to_add;
  return 0;
}

int is_operation(char c) {
  return c == '=' || c == '*' || c == '/' || c == '+' || c == '-' || c == '%';
}

//
//                 Parsing
//

parse_rv parse_op(const char* ptr, StringVec* expr_vec) {
  if (is_operation(*ptr)) {
    String temp = {0};
    if (string_init(&temp, 1) != 0) {
      return parse_rv_bad_alloc;
    }
    string_push_back(&temp, *ptr);
    if (str_vec_add(expr_vec, &temp)) {
      string_destr(&temp);
      return parse_rv_bad_alloc;
    }
  }
  return parse_rv_ok;
}

parse_rv parse_string(const String* str, StringVec* expr_vec) {
  char* ptr = str->_buf;
  while (*ptr != ';' && *ptr != '\0') {
    String temp = {0};
    if (string_init(&temp, 16) != 0) {
      return parse_rv_bad_alloc;
    }

    while (*ptr != ';' && isspace(*ptr)) {
      ptr++;
    }
    int is_op = is_operation(*ptr);

    while (!isspace(*ptr) && *ptr != ';' && (is_op == is_operation(*ptr))) {
      if (string_push_back(&temp, *ptr) != 0) {
        string_destr(&temp);
        return parse_rv_bad_alloc;
      }
      ptr++;
    }

    if (!string_is_empty(&temp)) {
      if (str_vec_add(expr_vec, &temp) != 0) {
        string_destr(&temp);
        return parse_rv_bad_alloc;
      }
    }
  }
  return parse_rv_ok;
}

int execute_operation(int a, int b, String* operation, MemoryCell* result) {
  switch (operation->_buf[0]) {
    case '+':
      result->value = a + b;
      return 0;
    case '-':
      result->value = a - b;
      return 0;
    case '*':
      result->value = a * b;
      return 0;
    case '/':
      result->value = a / b;
      return 0;
    case '%':
      result->value = a % b;
      return 0;
    default:
      return -1;
  }
}

parse_rv parse_expression(StringVec* expression, MemoryVec* mvec, FILE* out) {
  if (str_is_equal_charp(&expression->buf[0], "print")) {
    switch (expression->cnt) {
      case 1:
        mem_vec_print(mvec, out);
        return parse_rv_ok;
      case 0:
        return parse_rv_inv;
      default: {
        size_t index = find_index_byname(mvec, expression->buf[1]._buf);
        if (index == -1) {
          return parse_rv_uninit;
        }
        mem_cell_print(&mvec->arr[index], out);
        fputc('\n', out);
      }
    }
    return parse_rv_ok;
  }

  ll l_ind = find_index_byname(mvec, expression->buf[0]._buf);
  if (l_ind == -1) {
    MemoryCell temp;
    mem_cell_constr(&temp, expression->buf[0]._buf, 0);
    mem_vec_add(mvec, &temp);
    l_ind = find_index_byname(mvec, expression->buf[0]._buf);
  }
  MemoryCell* res_cell;
  res_cell = &mvec->arr[l_ind];

  if (!str_is_equal_charp(&expression->buf[1], "=")) {
    return parse_rv_inv;
  }

  int val1, val2;
  if (!if_i(expression->buf[2]._buf)) {
    size_t index = find_index_byname(mvec, expression->buf[2]._buf);
    if (index == -1) {
      return parse_rv_uninit;
    }
    val1 = mvec->arr[index].value;
  } else {
    val1 = strtol(expression->buf[2]._buf, NULL, 10);
  }
  if (expression->cnt == 3) {
    res_cell->value = val1;
    return parse_rv_ok;
  }
  if (expression->cnt != 5) {
    return parse_rv_inv;
  }

  if (!if_i(expression->buf[4]._buf)) {
    size_t index = find_index_byname(mvec, expression->buf[4]._buf);
    if (index == -1) {
      return parse_rv_uninit;
    }
    val2 = mvec->arr[index].value;
  } else {
    val2 = strtol(expression->buf[4]._buf, NULL, 10);
  }
  execute_operation(val1, val2, &expression->buf[3], res_cell);


  return parse_rv_ok;
}

parse_rv parse_file(FILE* in, FILE* out) {
  MemoryVec mvec = {0};
  String str = {0};
  StringVec parsed_vec = {0};
  if (mem_vec_constr(&mvec, 1) != 0) {
    return parse_rv_bad_alloc;
  }
  if (string_init(&str, 16) != 0) {
    mem_vec_destr(&mvec);
    return parse_rv_bad_alloc;
  }
  if (str_vec_init(&parsed_vec, 5) != 0) {
    mem_vec_destr(&mvec);
    string_destr(&str);
    return parse_rv_bad_alloc;
  }

  while (!feof(in)) {
    switch (getline(&str, in)) {
      case get_str_bad_alloc: {
        mem_vec_destr(&mvec);
        string_destr(&str);
        str_vec_dest(&parsed_vec);
        return parse_rv_bad_alloc;
      }
      case get_str_eof:
      case get_str_empty:
        break;

      default: {
        parse_rv s_code = parse_string(&str, &parsed_vec);
        if (s_code) {
          mem_vec_destr(&mvec);
          string_destr(&str);
          str_vec_dest(&parsed_vec);
          return s_code;
        }

        s_code = parse_expression(&parsed_vec, &mvec, out);
        if (s_code != parse_rv_ok) {
          mem_vec_destr(&mvec);
          str_vec_dest(&parsed_vec);
          string_destr(&str);
          return s_code;
        }
        str_vec_clear(&parsed_vec);
      }
    }
  }

  mem_vec_destr(&mvec);
  str_vec_dest(&parsed_vec);
  string_destr(&str);
  return 0;
}

//
//        MemoryCell methods
//

int mem_cell_constr(MemoryCell* cell, char* name, int value) {
  cell->name = (char*) malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(cell->name, name);
  cell->value = value;
  return 0;
}

int mem_cell_destr(MemoryCell* cell) {
  free(cell->name);
  cell->name = NULL;
  cell->value = 0;
  return 0;
}

int mem_cell_print(MemoryCell* cell, FILE* out) {
  fprintf(out, "%s %d", cell->name, cell->value);
  return 0;
}

//
//          MemoryVec methods
//

int mem_vec_constr(MemoryVec* vec, int cap) {
  if (cap < 1) {
    return 1;
  }
  vec->arr = (MemoryCell*) malloc(sizeof(MemoryCell) * cap);
  if (vec->arr == NULL) {
    return -1;
  }
  vec->cap = cap;
  vec->size = 0;
  return 0;
}

int mem_vec_destr(MemoryVec* vec) {
  for (int i = 0; i < vec->size; i++) {
    mem_cell_destr(&vec->arr[i]);
  }
  free(vec->arr);
  vec->arr = NULL;
  vec->size = 0;
  vec->cap = 0;
  return 0;
}

int mem_vec_resize(MemoryVec* vec, size_t new_size) {
  if (new_size < vec->size) {
    return 1;
  }

  MemoryCell* temp = (MemoryCell*) realloc(vec->arr, new_size * sizeof(MemoryCell));
  if (temp == NULL) {
    return -1;
  }
  vec->arr = temp;
  return 0;
}

int cmp_name(const void* a, const void* b) {
  MemoryCell* m1 = (MemoryCell*) a;
  MemoryCell* m2 = (MemoryCell*) b;
  return strcmp(m1->name, m2->name);
}

int mem_vec_sort(MemoryVec* vec) {
  qsort(vec->arr, vec->size, sizeof(MemoryCell), cmp_name);
  return 0;
}

int mem_vec_add(MemoryVec* vec, const MemoryCell* cell) {
  if (vec->size == vec->cap) {
    int i = mem_vec_resize(vec, vec->cap * 2);
    if (i != 0) {
      return i;
    }
    vec->cap *= 2;
  }

  vec->arr[vec->size++] = *cell;
  mem_vec_sort(vec);
  return 0;
}

int mem_vec_print(MemoryVec* vec, FILE* out) {
  for (int i = 0; i < vec->size; i++) {
    mem_cell_print(&vec->arr[i], out);
    fputc(' ', out);
  }
  fputc('\n', out);
  return 0;
}

ll find_index_byname(const MemoryVec* vec, char* name) {
  ll left = 0;
  MemoryCell temp;
  temp.name = name;
  if (vec->size == 0) {
    return -1;
  }
  ll right = vec->size - 1;
  while (left <= right) {
    ll mid = left + (right - left) / 2;

    int r = cmp_name(&vec->arr[mid], &temp);
    if (r == 0) {
      return mid;
    } else if (r < 0) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;
}