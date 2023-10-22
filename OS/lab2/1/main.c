#include <stdio.h>
#include <unistd.h>

int main() {
  printf("%d %d %d %d %d %d",
         getpid(),  //cur proc id
         getppid(), //parent proc id
         getgid(),  //real owner group id
         getuid(),  //real owner id
         getegid(), //eff owner group id
         geteuid()  //eff owner id
  );
}
