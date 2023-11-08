#ifndef L3_4_MAIL
#define L3_4_MAIL

#include "my_string.h"


typedef struct _address {
  String city;
  String street;
  unsigned int house_n;
  String building;
  unsigned int apt_n;
  String index; // 6 chars
} Address;

int address_constr(Address* _address, String* _city, String* _street, unsigned int _house_n, String* _building,
                   unsigned int apt_n);

typedef enum {
  get_rv_ok,
  get_rv_bad_alloc,
  get_rv_num_inv,
  get_rv_str_inv,
  get_rv_eof,
  get_rv_strlen_incorrect
} get_rv;

get_rv get_address(Address* addr, FILE* in);
int address_destr(Address* _address);

typedef struct _mail {
  Address recieve_addr;
  double weight;
  String mail_id; // 14 chars
  String creation_time; // "dd:MM:yyyy hh:mm:ss"
  String recieve_time;
} Mail;

int mail_constr(Mail* mail, Address* addr, double weight, String* mail_id, String* cr_time, String* rec_time);
get_rv get_mail(Mail* mail, FILE* in);
int mail_destr(Mail* mail);

typedef struct node {
  Mail* data;
  struct node* left;
  struct node* right;
} mail_bst_node;

int mail_bst_node_constr(mail_bst_node* node, Mail* data);
int mail_bst_node_destr(mail_bst_node* node);

typedef struct {
  mail_bst_node* root;
  int (* comp)(Mail*, Mail*);
} MailBST;

int bst_constr(MailBST* bst, int (* comp)(Mail*, Mail*));
int bst_destr(MailBST* bst);
int bst_add(MailBST* bst, Mail* data);
int bst_show(MailBST const* bst, FILE* stream);

typedef struct _post {
  Address* post_addr;
  MailBST* mails;
} Post;

int post_constr(Post* post, Address* _addr, MailBST* mails);
int post_destruct(Post* post);

#endif