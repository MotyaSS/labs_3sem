#include <stdlib.h>
#include <string.h>
#include "l3-5.h"


int student_dest(Student* st) {
  if (st == NULL) {
    return -1;
  }
  free(st->grades);
  return 0;
}

get_rv read_student(Student* st, FILE* in) {
  if (fscanf(in, "%u %32[^ ] %32[^ ] %16[^ ] %hhu %hhu %hhu %hhu %hhu\n", &st->id, st->name, st->surname,
             st->group, &st->grades[0], &st->grades[1], &st->grades[2], &st->grades[3], &st->grades[4]) != 9) {
    return get_inv_input;
  }
  return get_ok;
}

get_rv st_vec_get_from_file(StudentVec* vec, FILE* in) {
  while (!feof(in)) {
    Student* st = (Student*) malloc(sizeof(Student));
    if (!st) {
      return get_bad_alloc;
    }
    if (!(st->grades = (unsigned char*) malloc(sizeof(unsigned char) * GRADE_CNT))) {
      free(st);
      return get_bad_alloc;
    }

    if (read_student(st, in) != get_ok) {
      return get_inv_input;
    }

    if (st_vec_add(vec, st) != 0) {
      return get_bad_alloc;
    }
  }
  return get_ok;
}

int print_st_to_file(const Student* st, FILE* out) {
  if (st == NULL || out == NULL) {
    return -1;
  }
  double grades_avg = get_average_grade(st);
  fprintf(out, "%s %s %s %lf\n", st->name, st->surname, st->group, grades_avg);
  return 0;
}

int st_vec_init(StudentVec* vec, size_t cap) {
  if (cap == 0) {
    return -1;
  }
  vec->arr = (Student*) malloc(cap * sizeof(Student));
  if (vec->arr == NULL) {
    return -1;
  }
  vec->cap = cap;
  vec->size = 0;
  return 0;
}

int name_cmp(const void* s1, const void* s2) {
  Student* st1 = (Student*) s1;
  Student* st2 = (Student*) s2;
  return strcmp(st1->name, st2->name);
}

int id_cmp(const void* s1, const void* s2) {
  Student* st1 = (Student*) s1;
  Student* st2 = (Student*) s2;
  return st1->id > st2->id ? 1 : st1->id == st2->id ? 0 : -1;
}

int surname_cmp(const void* s1, const void* s2) {
  Student* st1 = (Student*) s1;
  Student* st2 = (Student*) s2;
  return strcmp(st1->surname, st2->surname);
}

int group_cmp(const void* s1, const void* s2) {
  Student* st1 = (Student*) s1;
  Student* st2 = (Student*) s2;
  return strcmp(st1->group, st2->group);
}

Student* st_find(StudentVec const* vec, sf_flag f_flag, union st_data data) {
  int (* cmp)(const void*, const void*);
  Student a;
  switch (f_flag) {
    case sf_name:
      strcpy(a.name, data.string);
      cmp = name_cmp;
      break;
    case sf_surname:
      strcpy(a.surname, data.string);
      cmp = surname_cmp;
      break;
    case sf_group:
      strcpy(a.group, data.string);
      cmp = group_cmp;
      break;
    case sf_id:
      a.id = data.id;
      cmp = id_cmp;
      break;
    default:
      return NULL;
  }
  for (int i = 0; i < vec->size; i++) {
    if (cmp(&a, &vec->arr[i]) == 0) {
      return &vec->arr[i];
    }
  }
  return NULL;
}

int st_sort(StudentVec* vec, sf_flag s_flag) {
  int (* cmp)(const void*, const void*);
  switch (s_flag) {
    case sf_name:
      cmp = name_cmp;
      break;
    case sf_surname:
      cmp = surname_cmp;
      break;
    case sf_group:
      cmp = group_cmp;
      break;
    case sf_id:
      cmp = id_cmp;
      break;
    default:
      return -1;
  }
  qsort(vec->arr, vec->size, sizeof(Student), cmp);
  return 0;
}

double get_average_grade(const Student* st) {
  double sum = 0;
  for (int i = 0; i < GRADE_CNT; i++) {
    sum += st->grades[i];
  }
  return sum / GRADE_CNT;
}

int st_vec_add(StudentVec* vec, Student* st) {
  if (vec->size == vec->cap) {
    Student* temp = realloc(vec->arr, (vec->cap * 2) * sizeof(Student));
    if (temp == NULL) {
      return -1;
    }
    vec->arr = temp;
    vec->cap = vec->cap * 2;
  }
  vec->arr[vec->size++] = *st;
  return 0;
}

int st_vec_dest(StudentVec* vec) {
  for (int i = 0; i < vec->size; i++) {
    student_dest(&vec->arr[i]);
  }
  free(vec->arr);
  vec->size = 0;
  vec->cap = 0;
  return 0;
}

int fprint_avg_higher_students(StudentVec const* vec, FILE* out) {
  size_t size = vec->size;
  double avg = 0;
  for (int i = 0; i < size; i++) {
    avg += get_average_grade(&vec->arr[i]);
  }
  avg = avg / size;
  fprintf(out, "Found by avg:\n");
  for (int i = 0; i < size; i++) {
    if (get_average_grade(&vec->arr[i]) > avg) {
      print_st_to_file(&vec->arr[i], out);
    }
  }
  fprintf(out, "__________________________________\n");
  return 0;
}