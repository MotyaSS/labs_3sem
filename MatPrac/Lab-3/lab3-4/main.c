#include <stdio.h>
#include "mail.h"

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

int comp(Mail* m1, Mail* m2) {
  int cmp = str1_cmp_str2(&m1->recieve_addr.index, &m2->recieve_addr.index);
  return cmp != 0 ? cmp : str1_cmp_str2(&m1->mail_id, &m2->mail_id);
}

void test_bst() {
  MailBST bst;
  bst_constr(&bst, comp);

  bst_show(&bst, stdout);
  bst_destr(&bst);
}

int main() {
  test_bst();
  /*
  String str;
  string_init(&str, 1);
  get_string(&str, stdin);
  show_string(&str);*/
}
