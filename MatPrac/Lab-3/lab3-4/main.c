#include <stdio.h>
#include "my_string.h"

int main() {
  String s1, s2;
  string_constr("I love Makima", &s1);
  string_constr("", &s2);
  printf("%d\n", string_is_equal(&s1, &s2));
  string_copy(&s1, &s2);
  printf("%s", s2._buf);
}
