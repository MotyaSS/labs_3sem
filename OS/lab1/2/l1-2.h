#ifndef OS_L1_2_h
#define OS_L1_2_h

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define LOGIN_LEN 6

typedef struct {
  char login[LOGIN_LEN + 1];
  unsigned int password;
  int sanctions;
} user;

typedef struct {
  user* users;
  size_t cap;
  size_t cur_size;
} user_db;

typedef enum {
  shut_down,
  login,
  get_time,
  get_date,
  logout,
  reg,
  help,
  sanction,
  undefined
} request;

typedef enum {
  login_pass_ok,
  login_too_log,
  pin_invalid
} get_login_pin_st_code;

typedef enum {
  login_success,
  already_logged_in,
  wrong_login,
  wrong_pin
} user_login_st_code;

typedef enum {
  logout_success,
  not_logged
} user_logout_st_code;

typedef enum {
  reg_success,
  reg_fail
} user_reg_st_code;

typedef enum {
  sanction_ok,
  user_not_found,
  wrong_conf_code
} user_sanction_st_code;

//  PROG LOGIC

int start_app();
void echo_help_message();
bool compare(char* s1, char* s2);
request get_request();
int request_switch_case(user_db* db, request rq, user** cur_login);

//  DATABASE

int db_construct(user_db* db, size_t pref_cap);
int db_expand(user_db* db);
int db_add_user(user_db* db, user _user);
int db_destruct(user_db* db);
user* db_get_user(user_db* db, char login[LOGIN_LEN + 1]);

//UI funcs

user_sanction_st_code user_sanction(user_db* db, int confirmation_code);
int user_login(user_db* db, user** cur_user);
int user_logout(user** cur_user);
int user_register(user_db* db);
int print_date(user* cur_user);
int print_time(user* cur_user);
int time_since(user* cur_user);

int parse_date(struct tm* time_);

#endif