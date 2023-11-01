#include <string.h>
#include <stdlib.h>
#include "l3-3.h"
#include "../../../my_flag_lib.h"

void show_employee(Employee const* emp) {
  printf("%d: %s %s %lf", emp->id, emp->name, emp->surname, emp->salary);
}

int comp_asc(void const* emp1, void const* emp2) {
  Employee* e1 = *(Employee**) emp1;
  Employee* e2 = *(Employee**) emp2;

  if (e1->salary != e2->salary) {
    return e1->salary > e2->salary;
  }
  if (strcmp(e1->surname, e2->surname) != 0) {
    return e1->surname > e2->surname;
  }
  if (strcmp(e1->name, e2->name) != 0) {
    return e1->name > e2->name;
  }
  return e1->salary > e2->id;
}

int comp_desc(void const* emp1, void const* emp2) {
  return comp_asc(emp2, emp1);
}

void emp_sort(Employee_vec* db, enum sort_flag flag) {
  if (flag == ASCEND) {
    qsort(*db->empv, db->size, sizeof(Employee), comp_asc);
  }

  if (flag == DESCEND) {
    qsort(*db->empv, db->size, sizeof(Employee), comp_desc);
  }
}