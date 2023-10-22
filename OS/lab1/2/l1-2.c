#include <stdio.h>
#include "l1-2.h"

void echo_help_message() {
  printf("You can always type \'exit\' to exit\n"
         "Type \'login\' to log into currently existing account;\n"
         "You also can type register to \'register\' a new one;\n"
         "Type \'logout\' to logout\n"
         "Type \'sanction\' to set user sanction;\n"
         "Type \'date\' or \'time\' to get date or time;\n"
         "Type \'help\' to get this message.\n");
}

bool compare(char* s1, char* s2) {
  while (*s1 != 0 && *s2 != 0) {
    if (*s1 != *s2) {
      return false;
    }
    s1++;
    s2++;
  }
  if (*s1 != 0 || *s2 != 0) {
    return false;
  }
  return true;
}

request get_request() {
  char buff[65];
  scanf("%64s", buff);
  if (compare(buff, "exit"))
    return shut_down;
  if (compare(buff, "register"))
    return reg;
  if (compare(buff, "login"))
    return login;
  if (compare(buff, "help"))
    return help;
  if (compare(buff, "sanction"))
    return sanction;
  if (compare(buff, "time"))
    return get_time;
  if (compare(buff, "date"))
    return get_date;
  if (compare(buff, "logout"))
    return logout;
  else
    return undefined;
}

int request_switch_case(user_db* db, const request rq, user** cur_user) {
  switch (rq) {
    case login:
      switch (user_login(db, cur_user)) {
        case already_logged_in:
          printf("You already logged in\n");
          break;
        case login_success:
          printf("login success\n");
          break;
        case wrong_login:
          printf("wrong login\n");
          break;
        case wrong_pin:
          printf("wrong pin\n");
          break;
      }
      break;
    case reg:
      switch (user_register(db)) {
        case reg_success:
          printf("successfully registered\n");
          break;
        case reg_fail:
          printf("registration failed\n");
          break;
      }
      break;
    case help:
      echo_help_message();
      break;
    case shut_down:
      printf("Bye!\n");
      break;
    case sanction: {
      int code;
      printf("confirm with code\n");
      scanf_s("%d", &code);
      switch (user_sanction(db, code)) {
        case user_not_found:
          printf("user not found\n");
          break;
        case wrong_conf_code:
          printf("wrong code\n");
          break;
        case sanction_ok:
          printf("sanction success\n");
          break;
      }
      break;
    }
    case get_date:
      print_date(*cur_user);
      break;
    case get_time:
      print_time(*cur_user);
      break;
    case logout:
      switch (user_logout(cur_user)) {
        case logout_success:
          printf("logout success\n");
          break;
        case not_logged:
          printf("you are not logged\n");
          break;
      }
      break;
    default:
      printf("undefined command\n");
  }
  return 0;
}

int start_app() {
  user_db db;
  size_t size__ = 10;
  if (db_construct(&db, size__) != 0) {
    return -1;
  }
  printf("%25s\n", "DOBRO POZHALOVAT");
  request rq = help;
  user* cur_user = NULL;
  echo_help_message();
  while (rq != shut_down) {
    rq = get_request();
    request_switch_case(&db, rq, &cur_user);
  }
  db_destruct(&db);
  return 0;
}
