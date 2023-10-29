#include <stdio.h>
#include <unistd.h>

int main() {
  fork();
  printf("Bomp!\n");
  fork();
  printf("Bump!\n");
  return 0;
}
