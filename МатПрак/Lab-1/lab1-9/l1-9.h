#ifndef L1_9_H
#define L1_9_H

static unsigned long int __rand_seed = 2023;

typedef enum {
  OK,
  INVALID_ARGC,
  INVALID_NUMBER_VALUE,
} st_code;

st_code input(int argc, const char* argv[]);
void start(int left, int right);

void fill_array_with_rands(int arr[], int size, int left_r, int right_r);
void print_array(int arr[], int size);
void swap(int* a, int* b);
void swap_max_and_min(int arr[], int size);
int find_closest_to_elem(const int arr[], int size, int elem);
void merge_arrays(const int arr_a[], const int arr_b[], int arr_c[], int size);

int get_random_int(int left, int right);
void set_random_seed(int seed);

#endif