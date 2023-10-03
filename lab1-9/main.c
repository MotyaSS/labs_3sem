#include "l1-9.h"
#include <stdio.h>
#define SIZE 10

void example() {
  int arr1[SIZE], arr2[SIZE], arr3[SIZE];
  fill_array_with_rands(arr1, SIZE, 0, 100);
  fill_array_with_rands(arr2, SIZE, 0, 100);
  print_array(arr1, SIZE);
  print_array(arr2, SIZE);
  merge_arrays(arr1, arr2, arr3, SIZE);
  print_array(arr3, SIZE);
}

int main(int argc, char* argv[]) {
  switch (input(argc, argv)) {
    case OK:
      printf("All OK\n");
      break;
    case INVALID_ARGC:
      printf("Invalid argument count\n");
      break;
    case INVALID_NUMBER_VALUE:
      printf("Invalid number entered\n");
      break;
  }
}
