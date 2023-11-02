#include "mail.h"

int address_constr(Address* _address, String* _city, String* _street, unsigned int _house_n, String* _building,
                   unsigned int apt_n) {
  _address->city = *_city;
  _address->street = *_street;
  _address->house_n = _house_n;
  _address->building = *_building;
  _address->apt_n = apt_n;
  return 0;
}

int address_destr(Address* _address) {
  free(_address);
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