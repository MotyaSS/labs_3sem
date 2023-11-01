#include <stdio.h>
#include <search.h>
#include "l3-3.h"
#include "../../../my_flag_lib.h"


int handle(int argc, char* argv[]) {
  if (argc != 4) {
    return inv_argc;
  }
  char* flag = argv[2];
  if (!if_flag(flag)) {
    return inv_flag;
  }
  flag++;
  if (flag[0] == 0 || flag[1] != 0) {
    return inv_flag;
  }

  enum sort_flag fl;

  switch (*flag) {
    case 'a':
      fl = ASCEND;
      break;
    case 'd':
      fl = DESCEND;
      break;
    default:
      return inv_flag;
  }

  FILE* in = fopen(argv[1], "r");
  if (!in) {
    return inv_file;
  }
  FILE* out = fopen(argv[3], "w");
  if (!out) {
    fclose(in);
    return inv_file;
  }

  Employee_vec empv;
  empv_constr(&empv);
  if (get_info_from_file(&empv, in) != get_emp_ok) {
    return inv_input;
  }

  emp_sort(&empv, fl);
  empv_destr(&empv);

}

int test(FILE* stream) {

}

int main(int argc, char* argv[]) {
  FILE* stream = fopen("test.txt", "r");
  Employee* t;
  printf("%d\n", get_employee(stream, &t));
  printf("%d", feof(stream));


  /*switch (handle(argc, argv)) {
    case ok:
      printf("all ok\n");
      break;
    case inv_argc:
      printf("invalid arg cnt\n");
      break;
    case inv_file:
      printf("invalid file\n");
      break;
    case inv_input:
      printf("invalid input\n");
      break;
    default:
      printf("unknown st code\n");
  }
  return 0;*/
}
