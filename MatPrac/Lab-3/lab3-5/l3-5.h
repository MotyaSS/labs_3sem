#ifndef L3_5_H
#define L3_5_H

#include <stdio.h>


#define BUFFSIZE 32
// Шаблон входных данных
/*
 * [id] [name] [surname] [group] [grade1] [grade2] ... \n
 * ...
 * */

typedef struct {
  unsigned int id;
  char name[BUFFSIZE + 1];
  char surname[BUFFSIZE + 1];
  char group[BUFFSIZE + 1];
  unsigned char* grades;
} Student;

typedef enum {
  sf_id,
  sf_name,
  sf_surname,
  sf_group,
  sf_unknown
} sf_flag;

union st_data {
  unsigned int id;
  char* string;
};

typedef enum {
  get_ok,
  get_bad_alloc,
  get_inv_input
} get_rv;

get_rv get_student(Student* st, FILE* in);
int student_dest(Student* st);
int print_st_to_file(Student* st, FILE* out);

typedef struct {
  Student* arr;
  size_t size;
  size_t cap;
} StudentVec;

int st_vec_init(StudentVec* vec, size_t cap);
get_rv st_vec_get_from_file(StudentVec* vec, FILE* in);
int st_vec_add(StudentVec* vec, Student* st);
Student* st_find(StudentVec const* vec, sf_flag f_flag,
                 union st_data); //third parameter is value itself, cant find - return NULL

int name_cmp(const void* s1, const void* s2);
int id_cmp(const void* s1, const void* s2);
int surname_cmp(const void* s1, const void* s2);
int group_cmp(const void* s1, const void* s2);

int st_sort(StudentVec* vec, sf_flag s_flag);
int st_vec_dest(StudentVec* vec);


#endif