#include <stdio.h>
#include "mail.h"
#include "l3-4.h"
#define INPUT_CONSOLE true

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

void test_bst() {
  MailBST bst;
  bst_constr(&bst, comp);

  bst_show(&bst, stdout);
  bst_destr(&bst);
}

int execute(FILE* in) {
  printf("It all starts here\n");
  Post post;
  Address* post_address = (Address*) malloc(sizeof(Address));
  MailBST* bst = (MailBST*) malloc(sizeof(MailBST));
  post_constr(&post, post_address, bst);
  if (!post_address || !bst) {
    post_destruct(&post);
    return -1;
  }
  bst_constr(bst, comp);

  printf("Lets get address of the Post\n");
  if (get_address(post_address, in) != get_rv_ok) {
    free(post_address);
    return -1;
  }

  String temp_str;
  string_init(&temp_str, 16);

  command cmd = cm_help_msg;
  cmd = command_execute(cmd, &post, in);
  while (cmd != cm_exit && cmd != cm_eof) {
    int code = getline(&temp_str, in);
    if (code == get_str_ok) {
      cmd = get_command(&temp_str);
      cmd = command_execute(cmd, &post, in);
    } else if (code != get_str_empty) {
      post_destruct(&post);
      return -1;
    }
  }

  post_destruct(&post);
  return 0;
}

int main() {
  FILE* in;
#ifdef INPUT_CONSOLE
#if INPUT_CONSOLE == true
  in = stdin;
#else
  in = fopen("in", "r");
#endif
#endif
  if (execute(in) != 0) {
    printf("something went wrong\n");
    return -1;
  }
#ifdef INPUT_CONSOLE
#if INPUT_CONSOLE == false
  fclose(in);
#endif
#endif

  /*String s;
  string_init(&s, 30);
  get_cur_time(&s);
  str_fprint(&s,stdout);*/

  /*
  String str;
  string_init(&str, 1);
  get_string(&str, stdin);
  show_string(&str);
  */
  return 0;
}
