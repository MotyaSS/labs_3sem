#ifndef L3_4_H
#define L3_4_H

#include <stdio.h>
#include "mail.h"


typedef enum {
  cm_help_msg,
  cm_exit,
  cm_add_mail,
  cm_find_delivered,
  cm_find_expired,
  cm_show,
  cm_unknown,
  cm_eof
} command;

int comp(Mail *m1, Mail *m2);
command command_execute(command cmd, Post *post, FILE *in);
command get_command(String const *str);

void echo_help();
command add_mail(Post *post, FILE *stream);
command find_delivered();
command find_expired();
command show();

#endif