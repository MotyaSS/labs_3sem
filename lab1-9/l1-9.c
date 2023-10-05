#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "l1-9.h"
#include "../my_flag_lib.h"

#define ARR_SIZE 10

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

//input

st_code input(const int argc, const char* argv[]) {
  if (argc != 3) {
    return INVALID_ARGC;
  }

  if (!if_i(argv[1]) || !if_i(argv[2])) {
    return INVALID_NUMBER_VALUE;
  }
  int left = strtol(argv[1], NULL, 10), right = strtol(argv[2], NULL, 10);

  if (left > right) {
    swap(&left, &right);
  }
  start(left, right);

  return OK;
}

void start(int left, int right) {
  set_random_seed((int) time(NULL));

  int arr[ARR_SIZE];
  fill_array_with_rands(arr, ARR_SIZE, left, right);
  printf("1. Unchanged:\t");
  print_array(arr, ARR_SIZE);
  swap_max_and_min(arr, ARR_SIZE);
  printf("Changed:\t");
  print_array(arr, ARR_SIZE);
  putchar('\n');
  int size = get_random_int(10, 10000);
  int* arr_A = (int*) malloc(sizeof(int) * size);
  int* arr_B = (int*) malloc(sizeof(int) * size);
  int* arr_C = (int*) malloc(sizeof(int) * size);
  fill_array_with_rands(arr_A, size, -1000, 1000);
  fill_array_with_rands(arr_B, size, -1000, 1000);
  merge_arrays(arr_A, arr_B, arr_C, size);
  print_array(arr_C, size);
  free(arr_A);
  free(arr_B);
  free(arr_C);
}

//array logic

void swap_max_and_min(int arr[], int size) {
  int index_min = 0, index_max = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] > arr[index_max]) {
      index_max = i;
    }
    if (arr[i] < arr[index_min]) {
      index_min = i;
    }
  }
  swap(&arr[index_min], &arr[index_max]);
}

int find_closest_to_elem(const int arr[], const int size, const int elem) {
  int closest = arr[0];
  for (int i = 1; i < size; i++) {
    if (abs(arr[i] - elem) < abs(closest - arr[i])) {
      closest = arr[i];
    }
  }
  return closest;
}

void merge_arrays(const int arr_a[], const int arr_b[], int arr_c[], int size) {
  for (int i = 0; i < size; i++) {
    arr_c[i] = arr_a[i] + find_closest_to_elem(arr_b, size, arr_a[i]);
  }
}

void print_array(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  putchar('\n');
}

void fill_array_with_rands(int arr[], int size, int left_r, int right_r) {
  for (int i = 0; i < size; i++) {
    arr[i] = get_random_int(left_r, right_r);
  }
}

//randoms

int get_random_int(int left, int right) {
  if (left > right) {
    return 0;
  }

  static const int A_rand = 1103515245;
  static const int C_rand = 12345;
  const int mod = right - left + 1;
  __rand_seed = (A_rand * __rand_seed + C_rand);
  return __rand_seed % mod + left;
}

void set_random_seed(int seed) {
  __rand_seed = seed;
}
