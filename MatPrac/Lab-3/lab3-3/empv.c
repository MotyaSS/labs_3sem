#include "l3-3.h"
#include "../../../my_flag_lib.h"
#include <stdlib.h>

int empv_constr(Employee_vec* empv) {
  empv->size = 0;
  empv->capacity = 10;
  empv->empv = malloc(sizeof(Employee*) * empv->capacity);
  if (empv->empv == NULL) {
    return -1;
  }
  return 0;
}

int empv_destr(Employee_vec* empv) {
  for (int i = 0; i < empv->size; i++) {
    Employee* t = empv->empv[i];
    free(t);
  }
  free(empv->empv);
  empv->capacity = 0;
  empv->size = 0;
  return 0;
}

int empv_add(Employee_vec* empv, Employee* emp) {
  if (empv->size >= empv->capacity) {
    empv->capacity *= 2;
    Employee** tv;
    tv = realloc(empv->empv, sizeof(Employee*) * empv->capacity);
    if (tv == NULL) {
      return -1;
    }
    empv->empv = tv;
  }
  empv->empv[empv->size++] = emp;
  return 0;
}

enum get_employee_st get_info_from_file(Employee_vec* empv, FILE* stream) {
  Employee* temp_emp;
  int code;
  while ((code = get_employee(stream, &temp_emp)) != get_emp_eof) {
    if (code == get_emp_bad_alloc || code == get_emp_inv_inp) {
      return code;
    }

    if (empv_add(empv, temp_emp) != 0) {
      return get_emp_bad_alloc;
    }
  }
  return get_emp_ok;
}

enum get_employee_st get_employee(FILE* stream, Employee** res) {
  Employee* new = (Employee*) malloc(sizeof(Employee));
  if (new == NULL) {
    return get_emp_bad_alloc;
  }
  char buf[BUFSIZ];
  if (my_fgets(stream, buf, BUFSIZ) == 1) {
    return get_emp_eof;
  }

  if (!if_u(buf)) {
    free(new);
    return get_emp_inv_inp;
  }

  new->id = strtoul(buf, NULL, 10);
  my_fgets(stream, new->name, BUFSIZ);
  my_fgets(stream, new->surname, BUFSIZ);
  if (my_fgets(stream, buf, BUFSIZ) != 0) {
    free(new);
    return get_emp_inv_inp;
  }

  if (!if_lf(buf)) {
    free(new);
    return get_emp_inv_inp;
  }
  new->salary = strtod(buf, NULL);
  *res = new;
  return get_emp_ok;
}
