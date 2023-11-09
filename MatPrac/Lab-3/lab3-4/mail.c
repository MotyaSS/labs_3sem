#include <ctype.h>
#include "mail.h"
#include "../../../my_flag_lib.h"


int address_constr(Address* _address, String* _city, String* _street, unsigned int _house_n, String* _building,
                   unsigned int apt_n, String* index) {
  _address->city = *_city;
  _address->street = *_street;
  _address->house_n = _house_n;
  _address->building = *_building;
  _address->apt_n = apt_n;
  _address->index = *index;
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

get_rv get_address(Address* addr, FILE* in) {
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

  if (init_strings(5, 10, &city, &street, &building, &index, &temp) != 0) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_rv_bad_alloc;
  }

  unsigned int house_n, apt_n;
  if ((a = getline(&city, in)) != get_str_ok) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_str_st_to_get_rv(a);
  }
  if ((a = getline(&street, in)) != get_str_ok) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_str_st_to_get_rv(a);
  }

  if ((a = getline(&temp, in)) != get_str_ok) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_str_st_to_get_rv(a);
  }
  if (!if_u(temp._buf)) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_rv_num_inv;
  }
  house_n = strtoul(temp._buf, NULL, 10);

  if ((a = getline(&building, in)) != get_str_empty && a != get_str_ok) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_str_st_to_get_rv(a);
  }
  if ((a = getline(&temp, in)) != get_str_ok) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_str_st_to_get_rv(a);
  }
  if (!if_u(temp._buf)) {
    return get_rv_num_inv;
  }
  apt_n = strtoul(temp._buf, NULL, 10);

  if (getline(&index, in) != get_str_ok) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_str_st_to_get_rv(a);
  }
  if (index._size != 6) {
    destr_strings(5, &city, &street, &building, &index, &temp);
    return get_rv_strlen_incorrect;
  }
  for (int i = 0; i < 6; i++) {
    if (!isdigit(index._buf[i])) {
      destr_strings(5, &city, &street, &building, &index, &temp);
      return get_rv_str_inv;
    }
  }
  address_constr(addr, &city, &street, house_n, &building, apt_n, &index);
  string_destr(&temp);
  return 0;
}

int address_destr(Address* _address) {
  string_destr(&_address->building);
  string_destr(&_address->index);
  string_destr(&_address->city);
  string_destr(&_address->street);
  return 0;
}

int mail_constr(Mail* mail, Address* addr, double weight, String* mail_id, String* cr_time, String* rec_time) {
  mail->recieve_addr = *addr;
  mail->weight = weight;
  mail->mail_id = *mail_id;
  mail->recieve_time = *rec_time;
  mail->creation_time = *cr_time;
  return 0;
}

int mail_destr(Mail* mail) {
  address_destr(&mail->recieve_addr);
  string_destr(&mail->mail_id);
  string_destr(&mail->creation_time);
  string_destr(&mail->recieve_time);
  return 0;
}

int post_constr(Post* post, Address* _addr, MailBST* mails) {
  post->mails = mails;
  post->post_addr = _addr;
  return 0;
}

int post_destruct(Post* post) {
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