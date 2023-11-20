#include <stdio.h>
#include "l3-5.h"
#include "../lab3-4/my_string.h"
#include "../../../my_flag_lib.h"
#include <string.h>


typedef enum {
  OK,
  INV_ARGC,
  INV_FILE,
  INV_INPUT,
  BAD_ALLOC
} st_code;

typedef enum {
  FIND,
  SORT,
  EXIT,
  UNKNOWN
} user_cmd;

sf_flag get_sf_flag(char* str) {
  if (strcmp(str, "id") == 0) {
    return sf_id;
  }
  if (strcmp(str, "group") == 0) {
    return sf_group;
  }
  if (strcmp(str, "name") == 0) {
    return sf_name;
  }
  if (strcmp(str, "surname") == 0) {
    return sf_surname;
  }
  return sf_unknown;
}

typedef enum {
  sfc_rv_ok,
  sfc_rv_bad_alloc,
  sfc_rv_flag_unknown,
  sfc_rv_value_inv
} sf_cmd_rv;

sf_cmd_rv cmd_sort(StudentVec* vec) {
  String temp;
  if (string_init(&temp, 4) != 0) {
    return sfc_rv_bad_alloc;
  }
  printf("Enter flag to sort\n");
  if (getline(&temp, stdin) == get_str_bad_alloc) {
    return sfc_rv_bad_alloc;
  }
  sf_flag sort_fl = get_sf_flag(temp._buf);
  if (sort_fl == sf_unknown) {
    return sfc_rv_flag_unknown;
  }
  st_sort(vec, sort_fl);
  return sfc_rv_ok;
}

sf_cmd_rv cmd_find(StudentVec* vec, FILE* out) {
  String temp;
  if (string_init(&temp, 4) != 0) {
    return sfc_rv_bad_alloc;
  }
  printf("Enter flag to search\n");
  if (getline(&temp, stdin) == get_str_bad_alloc) {
    return sfc_rv_bad_alloc;
  }
  sf_flag find_fl = get_sf_flag(temp._buf);
  printf("Enter value\n");
  if (getline(&temp, stdin) == get_str_bad_alloc) {
    return sfc_rv_bad_alloc;
  }
  union st_data a;
  switch (find_fl) {
    case sf_unknown:
      return sfc_rv_flag_unknown;
    case sf_id:
      if (!if_u(temp._buf)) {
        return sfc_rv_value_inv;
      }
      a.id = strtoul(temp._buf, NULL, 10);
    default:
      a.string = temp._buf;
  }
  Student* student = st_find(vec, find_fl, a);
  if (student == NULL) {
    printf("Student not found\n");
    return 0;
  }
  print_st_to_file(student, stdout);
  printf("Do you want to print data to file? (y for yes)\n");
  if (getline(&temp, stdin) == get_str_bad_alloc) {
    return sfc_rv_bad_alloc;
  }
  if (temp._buf[0] == 'y' && temp._buf[1] == '\0') {
    print_st_to_file(student, out);
  }
  string_destr(&temp);
  return 0;
}

user_cmd get_cmd(char* str) {
  if (strcmp(str, "exit") == 0) {
    return EXIT;
  }
  if (strcmp(str, "find") == 0) {
    return FIND;
  }
  if (strcmp(str, "sort") == 0) {
    return SORT;
  }
  return UNKNOWN;
}

int cmd_exec(StudentVec* vec, FILE* out, user_cmd cmd) {
  switch (cmd) {
    case SORT:
      switch (cmd_sort(vec)) {
        case sfc_rv_bad_alloc:
          return -1;
        case sfc_rv_flag_unknown:
          printf("flag unknown\n");
        case sfc_rv_ok:
          return 0;
      }
      return 0;
    case FIND:
      switch (cmd_find(vec, out)) {
        case sfc_rv_bad_alloc:
          return -1;
        case sfc_rv_value_inv:
          printf("value invalid\n");
          return 0;
        case sfc_rv_flag_unknown:
          printf("flag unknown\n");
        case sfc_rv_ok:
          return 0;
      }
      return 0;
    case EXIT:
      printf("Bye!\n");
      return 0;
    case UNKNOWN:
      printf("Unknown cmd\n");
      return 0;
  }

}

st_code start(int argc, char** argv) {
  if (argc != 3) {
    return INV_ARGC;
  }
  FILE* in = fopen(argv[1], "r");
  if (!in) {
    return INV_FILE;
  }
  FILE* out = fopen(argv[2], "w");
  if (!out) {
    fclose(in);
    return INV_FILE;
  }
  StudentVec s_vec;
  if (st_vec_init(&s_vec, 1) != 0) {
    fclose(in);
    fclose(out);
    return BAD_ALLOC;
  }
  switch (st_vec_get_from_file(&s_vec, in)) {
    case get_bad_alloc:
      st_vec_dest(&s_vec);
      fclose(in);
      fclose(out);
      return BAD_ALLOC;
    case get_inv_input:
      st_vec_dest(&s_vec);
      fclose(in);
      fclose(out);
      return INV_INPUT;
  }
  user_cmd cmd = SORT;
  String temp;
  if (string_init(&temp, 10) != 0) {
    st_vec_dest(&s_vec);
    fclose(in);
    fclose(out);
    return BAD_ALLOC;
  }
  while (!feof(stdin) && cmd != EXIT) {
    switch (getline(&temp, stdin)) {
      case get_str_bad_alloc:
        st_vec_dest(&s_vec);
        string_destr(&temp);
        fclose(in);
        fclose(out);
        return BAD_ALLOC;
      case get_str_eof:
        st_vec_dest(&s_vec);
        string_destr(&temp);
        fclose(in);
        fclose(out);
        return OK;
    }
    cmd = get_cmd(temp._buf);
    cmd_exec(&s_vec, out, cmd);
  }

  st_vec_dest(&s_vec);
  string_destr(&temp);
  fclose(in);
  fclose(out);
  return OK;
}

int main(int argc, char** argv) {
  switch (start(argc, argv)) {
    case OK:
      printf("OK\n");
    case INV_ARGC:
      printf("invalid argument count\n");
    case INV_FILE:
      printf("invalid file\n");
    case BAD_ALLOC:
      printf("bad alloc\n");
    case INV_INPUT:
      printf("invalid input\n");
  }
  return 0;
}