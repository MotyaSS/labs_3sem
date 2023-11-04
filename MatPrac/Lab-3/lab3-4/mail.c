#include "mail.h"
#include "../../../my_flag_lib.h"


int address_constr(Address *_address, String *_city, String *_street, unsigned int _house_n, String *_building,
                   unsigned int apt_n) {
  _address->city = *_city;
  _address->street = *_street;
  _address->house_n = _house_n;
  _address->building = *_building;
  _address->apt_n = apt_n;
  return 0;
}

get_rv get_str_st_to_get_rv(get_str_st a) {
  switch (a) {
    case get_str_eof:
      return get_rv_eof;
    case get_str_empty:
      return get_rv_str_inv;
    case get_str_bad_alloc:
      return get_rv_bad_alloc;
    default:
      return get_rv_ok;
  }
}

#include <stdarg.h>


int destr_strings(int cnt, ...) {
  va_list ap;
  va_start(ap, cnt);
  for (int i = 0; i < cnt; i++) {
    String *s = va_arg(ap, String*);
    string_destr(s);
  }
  va_end(ap);
  return 0;
}

int init_strings(int n, int cnt, ...) {
  va_list ap;
  va_start(ap, cnt);
  for (int i = 0; i < cnt; i++) {
    String *s = va_arg(ap, String*);
    if (string_init(s, n) != 0)
      return -1;
  }
  return 0;
}

int free_strings(int cnt, ...) {
  va_list ap;
  va_start(ap, cnt);
  for (int i = 0; i < cnt; i++) {
    String *s;
    if (!(s = va_arg(ap, String*))) {
      free(s);
    }
  }
  va_end(ap);
  return 0;
}

get_rv get_address(Address *addr, FILE *in) {
  /*
   адрес получателя
    город
    улица
    номер дома
    корпус
    квартира
    индекс(6 симолов)
   */
  printf("Enter city\n"
         "street\n"
         "house number\n"
         "building\n"
         "flat number\n"
         "index\n");
  int a;
  String city, street, building, index, temp;

  if (init_strings(10, 5, &city, &street, &building, &index, &temp) != 0) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_rv_bad_alloc;
  }

  unsigned int house_n, apt_n;
  if ((a = get_string(&city, in)) != get_str_ok) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_str_st_to_get_rv(a);
  }
  if ((a = get_string(&street, in)) != get_str_ok) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_str_st_to_get_rv(a);
  }

  if ((a = get_string(&temp, in)) != get_str_ok) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_str_st_to_get_rv(a);
  }
  if (!if_u(temp._buf)) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_rv_num_inv;
  }
  house_n = strtoul(temp._buf, NULL, 10);

  if ((a = get_string(&building, in)) != get_str_ok) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_str_st_to_get_rv(a);
  }
  if ((a = get_string(&temp, in)) != get_str_ok) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_str_st_to_get_rv(a);
  }
  if (!if_u(temp._buf)) {
    return get_rv_num_inv;
  }
  apt_n = strtoul(temp._buf, NULL, 10);

  if (get_string(&index, in) != get_str_eof) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_str_st_to_get_rv(a);
  }
  address_constr(addr, &city, &street, house_n, &building, apt_n);
  string_destr(&temp);
  return 0;
}

int address_destr(Address *_address) {

  free(_address);
  return 0;
}

int mail_constr(Mail *mail, Address *addr, double weight, String *mail_id, String *cr_time, String *rec_time) {
  mail->recieve_addr = *addr;
  mail->weight = weight;
  mail->mail_id = *mail_id;
  mail->recieve_time = *rec_time;
  mail->creation_time = *cr_time;
  return 0;
}

int mail_destr(Mail *mail) {
  address_destr(&mail->recieve_addr);
  string_destr(&mail->mail_id);
  string_destr(&mail->creation_time);
  string_destr(&mail->recieve_time);
  return 0;
}

int post_constr(Post *post, Address *_addr, MailBST *mails) {
  post->mails = mails;
  post->post_addr = _addr;
  return 0;
}

int post_destruct(Post *post) {
  if (!post->post_addr) {
    address_destr(post->post_addr);
    free(post->post_addr);
  }
  if (!post->mails) {
    bst_destr(post->mails);
    free(post->mails);
  }
  return 0;
}