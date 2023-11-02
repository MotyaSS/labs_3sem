#ifndef L3_3_H
#define L3_3_H

#include <stdio.h>

enum sort_flag {
  DESCEND,
  ASCEND
};

enum get_employee_st {
  get_emp_ok,
  get_emp_inv_inp,
  get_emp_bad_alloc,
  get_emp_eof
};

typedef enum {
  ok,
  inv_argc,
  inv_flag,
  inv_file,
  inv_input
} st;

typedef struct _employee {
  unsigned int id;
  char name[BUFSIZ];
  char surname[BUFSIZ];
  double salary;
} Employee;

typedef struct {
  Employee** empv;
  size_t capacity;
  size_t size;
} Employee_vec;

int empv_constr(Employee_vec* empv);
int empv_destr(Employee_vec* vec);

void show_employee(Employee const* emp);
enum get_employee_st get_employee(FILE* stream, Employee** res);
enum get_employee_st get_info_from_file(Employee_vec* empv, FILE* stream);
int print_emp_to_file(FILE* stream, Employee const* emp);
int print_empv_to_file(FILE* stream, Employee_vec const* empv);

int comp_asc(void const* emp1, void const* emp2);
int comp_desc(void const* emp1, void const* emp2);

void empv_sort(Employee_vec* empv, enum sort_flag flag);

#endif