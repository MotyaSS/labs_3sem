#include "l1-2.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

get_login_pin_st_code get_login_pin(char* login, int* pin) {
  char pin_buf[513];
  scanf("%s%s", login, pin_buf);
  char* end;
  *pin = strtol(pin_buf, &end, 10);
  if (end != pin_buf + strlen(pin_buf)) {
    return pin_invalid;
  }

  if (strlen(login) > 6) {
    return login_too_log;
  }
  if (*pin >= 100000 || *pin <= 0) {
    return pin_invalid;
  }
  return login_pass_ok;
}

int user_login(user_db* db, user** cur_user) {
  if (*cur_user != NULL) {
    return already_logged_in;
  }
  printf("enter login and password\n");
  char login[512 + 1];
  int pin;
  if (get_login_pin(login, &pin) != 0) {
    return 1;
  }
  user* a = db_get_user(db, login);
  if (a == NULL) {
    return wrong_login;
  }
  if (a->password == pin) {
    *cur_user = a;
    return login_success;
  }
  return wrong_pin;
}

int user_logout(user** cur_user) {
  if (cur_user == NULL) {
    return not_logged;
  }
  *cur_user = NULL;
  return logout_success;
}

int user_register(user_db* db) {
  printf("enter login and password\n");
  char login[513];
  int pin;
  if (get_login_pin(login, &pin) != login_pass_ok) {
    return reg_fail;
  }
  user a;
  a.password = pin;
  strncpy(a.login, login, LOGIN_LEN);
  if (db_add_user(db, a) == 0) {
    return reg_success;
  }
  return reg_fail;
}

int print_date(user* cur_user) {
  if (cur_user == NULL) {
    printf("you are not logged\n");
    return -1;
  }
  if (cur_user->sanctions == 0) {
    printf("SANCTIONED\n");
    return 1;
  }
  if (cur_user->sanctions != -1) {
    cur_user->sanctions -= 1;
  }
  time_t t = time(0);
  struct tm cur_time = *localtime(&t);
  printf("%02d-%02d-%4d\n", cur_time.tm_mday, cur_time.tm_mon + 1, cur_time.tm_year + 1900);
  return 0;
}

int print_time(user* cur_user) {
  if (cur_user == NULL) {
    printf("you are not logged\n");
    return -1;
  }
  if (cur_user->sanctions == 0) {
    printf("SANCTIONED\n");
    return 1;
  }
  if (cur_user->sanctions != -1) {
    cur_user->sanctions -= 1;
  }
  time_t t = time(NULL);
  struct tm cur_time = *localtime(&t);
  printf("%02d-%02d-%02d\n", cur_time.tm_hour, cur_time.tm_min, cur_time.tm_sec);
  return 0;
}

user_sanction_st_code user_sanction(user_db* db, int confirmation_code) {
  static int code = 12345;
  if (code != confirmation_code) {
    return wrong_conf_code;
  }
  char login[512 + 1];
  login[512] = 0;
  printf("enter login\n");
  scanf_s("%512s", login);
  printf("enter sanctions\n");
  int sanctions;
  scanf_s("%d", &sanctions);
  user* u = db_get_user(db, login);
  if (u == NULL) {
    return user_not_found;
  }
  u->sanctions = sanctions;
  return sanction_ok;
}

int time_since(user* cur_user) {
  struct tm t;
  t.tm_sec = 0;
  t.tm_min = 0;
  t.tm_hour = 0;  
  printf("enter date in format DD-MM-YYYY\n");
  if (parse_date(&t) != 0) {

  }
  time_t dt = mktime(&t);
  printf("enter flag\n");
  int a = getchar();
  if (a != '-') {

  }
  a = getchar();
  int v;
  if ((v = getchar()) != '\n') {
    while ((v = getchar()) != '\n');
    return -1;
  }
  switch (a) {
    case 's':
      break;
    case 'm':
      break;
    case 'h':
      break;
    case 'y':
      break;
    default:
      return -1;
  }

  return 0;
}

int parse_date(struct tm* time_) {
  long long day = 0, month = 0, year = 0;
  int a;
  while ((a = getchar()) != '-') {
    if (!isdigit(a))
      return -1;
    day = day * 10 + a - '0';
  }
  while ((a = getchar()) != '-') {
    if (!isdigit(a))
      return -1;
    month = month * 10 + a - '0';
  }
  while (isdigit(a = getchar())) {
    year = year * 10 + a - '0';
  }
  if (a != '\n')
    return -1;
  time_t t = time(0);
  struct tm cur_tm = *localtime(&t);
  if (month > 12)
    return -1;
  if (year > cur_tm.tm_year + 1900) {
    return -1;
  }

  if (day > 31) {
    return -1;
  }

  switch (month) {
    case 2:
      if (year % 4 == 0 || year % 100 != 0 && year % 400 == 0) {
        if (day > 29)
          return -1;
      } else if (day > 28)
        return -1;
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      if (day > 30)
        return -1;
    default:
      break;
  }
  year -= 1900;
  month -= 1;
  if (year == cur_tm.tm_year) {
    if (month > cur_tm.tm_mon)
      return -1;
    if (month == cur_tm.tm_mon) {
      if (day > cur_tm.tm_mday)
        return -1;
    }
  }

  time_->tm_year = year;
  time_->tm_mon = month;
  time_->tm_mday = day;
  return 0;
}
