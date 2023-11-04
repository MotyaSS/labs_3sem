#include "l3-4.h"


int comp(Mail *m1, Mail *m2) {
  int cmp = str1_cmp_str2(&m1->recieve_addr.index, &m2->recieve_addr.index);
  return cmp != 0 ? cmp : str1_cmp_str2(&m1->mail_id, &m2->mail_id);
}

void echo_help() {
  printf(""
         "Welcome!\n"
         "type 'add' to add mail\n"
         "type 'show' to print sorted mail list\n"
         "type 'exit' to exit\n"
         "type 'fe' to find expired\n"
         "type 'fd' to find delivered\n"
         "type 'show' to show all mails\n"
         "type 'help' to get this message\n");
}

command command_execute(command cmd, Post *post, FILE *in) {
  switch (cmd) {
    case cm_add_mail:
      return add_mail(post, in);
    case cm_find_delivered:
      return find_delivered();
    case cm_find_expired:
      return find_expired();
    case cm_show:
      return show();
    case cm_help_msg:
      echo_help();
    case cm_exit:
    default:
      return cmd;
  }
}

command get_command(String const *str) {
  if (str_is_equal_charp(str, "show")) {
    return cm_show;
  }
  if (str_is_equal_charp(str, "exit")) {
    return cm_exit;
  }
  if (str_is_equal_charp(str, "help")) {
    return cm_help_msg;
  }
  if (str_is_equal_charp(str, "add")) {
    return cm_add_mail;
  }
  if (str_is_equal_charp(str, "fd")) {
    return cm_find_delivered;
  }
  if (str_is_equal_charp(str, "fe")) {
    return cm_find_expired;
  }
  return cm_unknown;
}

command add_mail(Post *post, FILE *stream) {
  /*
  адрес получателя
   город
   улица
   номер дома
   корпус
   квартира
   индекс(6 симолов)
  вес посылки
  идентиффикатор (14 символов)
  время создания
  */
  printf("Введем адрес:\n");
}

command find_delivered() {
  return cm_find_delivered;
}

command find_expired() {

}

command show() {

}