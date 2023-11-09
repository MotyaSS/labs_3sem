#ifndef L3_4_H
#define L3_4_H
#define CLEAR_CONSOLE false

#include <stdio.h>
#include "mail.h"
#include <stdbool.h>
#include <time.h>


typedef enum {
  cm_help_msg,
  cm_exit,
  cm_add_mail,
  cm_find_delivered,
  cm_find_expired,
  cm_show,
  cm_find_mail,
  cm_unknown,
  cm_eof
} command;

int comp(Mail* m1, Mail* m2);
command command_execute(command cmd, Post* post, FILE* in);
command get_command(String const* str);

typedef enum {
  mail_rv_ok,
  mail_rv_eof,
  mail_rv_fail,
} mail_rv;

int get_cur_time(String* time);
int compare_time(String const* time1, String const* time2);
int cast_string_to_time(String const* str, struct tm* time);
bool is_time_valid(String const* str);

void echo_help();
mail_rv add_mail(Post* post, FILE* stream);

int time_cmp(Mail* m1, Mail* m2);
int find_delivered(Post const* post);
int find_mail(Post const* post, FILE* in);
int find_expired(Post const* post);
void show(Post const* post);

#endif