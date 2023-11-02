#include <stdio.h>
#include "my_string.h"

void test_string() {
  String s1, s2;
  string_constr("Plainy plains", &s1);
  string_init(&s2, 13);

  printf("%d\n", str1_cmp_str2(&s1, &s2));
  string_copy(&s1, &s2);

  show_string(&s1);
  show_string(&s2);

  printf("%d\n", string_is_equal(&s1, &s2));

  string_clear(&s1);
  printf("1 :");
  show_string(&s1);

  printf("2 :");
  show_string(&s2);

  string_destr(&s1);
  string_destr(&s2);
}

int main() {
  test_string();
  String str;
  string_init(&str, 1);
  get_string(&str, stdin);
  show_string(&str);
}
