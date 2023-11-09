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
#ifdef CLEAR_CONSOLE
#if CLEAR_CONSOLE == true
  system("cls");
#endif
#endif
  switch (cmd) {
    case cm_add_mail: {
      int code;
      if ((code = add_mail(post, in)) != mail_rv_ok) {
        if (code == mail_rv_eof) {
          return cm_eof;
        }
        printf("adding failed\n");
      }
      return cmd;
    }
    case cm_find_delivered:
      find_delivered(post);
      return cmd;
    case cm_find_expired:
      find_expired(post);
      return cmd;
    case cm_show:
      show(post);
      return cmd;
    case cm_help_msg:
      echo_help();
      return cmd;
    case cm_exit:
      return cmd;
    default:
      printf("command unknown\n");
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
  strftime(str->_buf, str->_cap, "%d-%m-%Y %H:%M:%S", time);
  return 0;
}

int compare_time(String const* time1, String const* time2) {
  struct tm t1, t2;
  cast_string_to_time(time1, &t1);
  cast_string_to_time(time2, &t2);
  if (t1.tm_year != t2.tm_year) {
    return t1.tm_year > t2.tm_year ? 1 : -1;
  }
  if (t1.tm_mon != t2.tm_mon) {
    return t1.tm_mon > t2.tm_mon ? 1 : -1;
  }
  if (t1.tm_mday != t2.tm_mday) {
    return t1.tm_mday > t2.tm_mday ? 1 : -1;
  }
  if (t1.tm_hour != t2.tm_hour) {
    return t1.tm_hour > t2.tm_hour ? 1 : -1;
  }
  if (t1.tm_min != t2.tm_min) {
    return t1.tm_min > t2.tm_min ? 1 : -1;
  }
  if (t1.tm_sec != t2.tm_sec) {
    return t1.tm_sec > t2.tm_sec ? 1 : -1;
  }
  return 0;
}

int cast_string_to_time(String const* str, struct tm* time) {
  if (sscanf(str->_buf, "%u:%u:%u%u:%u:%u", &time->tm_mday, &time->tm_mon, &time->tm_year, &time->tm_hour,
             &time->tm_min, &time->tm_sec) != 6) {
    return -1;
  }
  return 0;
}

bool is_time_valid(String const* str) {
  struct tm time;
  if (cast_string_to_time(str, &time) == -1) {
    return false;
  }
  if (time.tm_mon > 12) {
    return false;
  }

  int target_day;
  switch (time.tm_mon) {
    case 2:
      if (time.tm_year % 400 == 0 || (time.tm_year % 100 != 0 && time.tm_year % 4 == 0)) {
        target_day = 29;
      } else {
        target_day = 28;
      }
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      target_day = 30;
      break;
    default:
      target_day = 31;
  }
  if (time.tm_mday > target_day) {
    return false;
  }
  if (time.tm_hour >= 24 || time.tm_min >= 60 || time.tm_sec >= 60) {
    return false;
  }

  return true;
}

mail_rv add_mail(Post* post, FILE* stream) {
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
  if ((code = get_address(&addr, stream)) != get_rv_ok) {
    destr_strings(4, &mail_id, &r_time, &c_time, &weight_t);
    free(mail);
    if (code == get_rv_eof) {
      return mail_rv_eof;
    }
    return mail_rv_fail;
  }

  printf("Enter mail weight\n");
  if ((code = getline(&weight_t, stream)) != get_str_ok) {
    address_destr(&addr);
    destr_strings(4, &mail_id, &r_time, &c_time, &weight_t);
    free(mail);
    if (code == get_rv_eof) {
      return mail_rv_eof;
    }
    return mail_rv_fail;
  }
  if (weight_t._buf[0] == '-' || !if_lf(weight_t._buf)) {
    address_destr(&addr);
    destr_strings(4, &mail_id, &r_time, &c_time, &weight_t);
    free(mail);
    return mail_rv_fail;
  }
  weight = strtod(weight_t._buf, NULL);

  printf("Enter mail id\n");
  if ((code = getline(&mail_id, stream)) != get_str_ok || mail_id._size != 14) {
    address_destr(&addr);
    destr_strings(4, &mail_id, &r_time, &c_time, &weight_t);
    free(mail);
    if (code == get_rv_eof) {
      return mail_rv_eof;
    }
    return mail_rv_fail;
  }

  printf("If mail is received print receipt time in Greenwich (DD:MM:YYYY hh:mm:ss), else - hit \\n\n");
  code = getline(&r_time, stream);
  if (code != get_str_empty && (code != get_str_ok || !is_time_valid(&r_time))) {
    address_destr(&addr);
    destr_strings(4, &mail_id, &r_time, &c_time, &weight_t);
    free(mail);
    if (code == get_rv_eof) {
      return mail_rv_eof;
    }
    return mail_rv_fail;
  }
  get_cur_time(&c_time);
  mail_constr(mail, &addr, weight, &mail_id, &c_time, &r_time);
  if (bst_add(post->mails, mail) != 0) {
    return mail_rv_fail;
  }
  return mail_rv_ok;
}

int time_cmp(Mail* m1, Mail* m2) {
  return compare_time(&m1->recieve_time, &m2->recieve_time) == 1 ? 1 : -1;
}

int _assemble_bst(MailBST* bst1, mail_bst_node const* node) {
  if (node == NULL) {
    return 0;
  }
  if (!string_is_empty(&node->data->recieve_time) &&
      bst_add(bst1, node->data) != 0) {
    return -1;
  }
  if (_assemble_bst(bst1, node->left) != 0) {
    return -1;
  }
  if (_assemble_bst(bst1, node->right) != 0) {
    return -1;
  }
  return 0;
}

int find_delivered(Post const* post) {
  MailBST tempBST;
  bst_constr(&tempBST, time_cmp);
  if(_assemble_bst(&tempBST, post->mails->root) != 0){
    return -1;
  }
  bst_show(&tempBST, stdout);
  bst_destr(&tempBST);
  return 0;
}

int find_expired(Post const* post) {

}

void show(Post const* post) {
  bst_show(post->mails, stdout);
}