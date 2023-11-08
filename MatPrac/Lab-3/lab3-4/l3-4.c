#include <time.h>
#include "l3-4.h"
#include "../../../my_flag_lib.h"


int comp(Mail* m1, Mail* m2) {
  int cmp = str1_cmp_str2(&m1->recieve_addr.index, &m2->recieve_addr.index);
  return cmp != 0 ? cmp : str1_cmp_str2(&m1->mail_id, &m2->mail_id);
}

void echo_help() {
  printf(""
         "type 'add' to add mail\n"
         "type 'show' to print sorted mail list\n"
         "type 'exit' to exit\n"
         "type 'fe' to find expired\n"
         "type 'fd' to find delivered\n"
         "type 'show' to show all mails\n"
         "type 'help' to get this message\n");
}

command command_execute(command cmd, Post* post, FILE* in) {
  switch (cmd) {
    case cm_add_mail: {
      int code;
      if ((code = add_mail(post, in)) != mail_rv_ok) {
        if (code == mail_rv_eof) {
          return cm_eof;
        }
        printf("adding failed\n");
      }
      return cm_add_mail;
    }
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

command get_command(String const* str) {
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

int get_cur_time(String* str) {
  time_t t = time(0);
  struct tm* time = gmtime(&t);
  strftime(str->_buf, str->_size, "%d-%m-%Y %H:%M:%S", time);
  return 0;
}

int compare_time(String const* time1, String const* time2) {

}

int is_time_valid(String* str) {
  struct tm timeInfo;
  int result = strptime(str->_buf, "dd:MM:yyyy hh:mm:ss", &timeInfo);

  // Check if the entire input string was consumed
  if (result == str->_size) {
    return 0;
  } else {
    return -1;
  }
}

mail_rv add_mail(Post* post, FILE* stream) {
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
  Mail* mail = (Mail*) malloc(sizeof(Mail));
  if (mail == NULL) {
    return mail_rv_fail;
  }
  Address addr;
  String mail_id, r_time, c_time, weight_t;
  double weight;
  if (init_strings(4, 20, &mail_id, &r_time, &c_time, &weight_t) != 0) {
    destr_strings(4, &mail_id, &r_time, &c_time, &weight_t);
    free(mail);
    return mail_rv_fail;
  }
  printf("Enter mail receive address:\n");
  int code;
  if ((code = get_address(&mail->recieve_addr, stream)) != get_rv_ok) {
    destr_strings(4, &mail_id, &r_time, &c_time, &weight_t);
    free(mail);
    if (code == get_rv_eof) {
      return mail_rv_eof;
    }
    return mail_rv_fail;
  }

  printf("Enter mail weight\n");
  if ((code = get_string(&weight_t, stream)) != get_str_ok) {
    destr_strings(4, &mail_id, &r_time, &c_time, &weight_t);
    free(mail);
    if (code == get_rv_eof) {
      return mail_rv_eof;
    }
    return mail_rv_fail;
  }
  if (weight_t._buf[0] == '-' || !if_lf(weight_t._buf)) {
    destr_strings(4, &mail_id, &r_time, &c_time, &weight_t);
    free(mail);
    return mail_rv_fail;
  }
  weight = strtod(weight_t._buf, NULL);

  printf("Enter mail id\n");
  if ((code = get_string(&mail_id, stream)) != get_str_ok) {
    destr_strings(4, &mail_id, &r_time, &c_time, &weight_t);
    free(mail);
    if (code == get_rv_eof) {
      return mail_rv_eof;
    }
    return mail_rv_fail;
  }
  printf("If mail is received print receive time, else - hit \\n\n");
  if ((code = get_string(&mail_id, stream)) != get_str_ok && code != get_str_empty) {
    destr_strings(4, &mail_id, &r_time, &c_time, &weight_t);
    free(mail);
    if (code == get_rv_eof) {
      return mail_rv_eof;
    }
    return mail_rv_fail;
  }

  mail_constr(mail, &addr, weight, &mail_id, &c_time, &r_time);

  return mail_rv_ok;
}

command find_delivered() {
  return cm_find_delivered;
}

command find_expired() {

}

command show() {

}