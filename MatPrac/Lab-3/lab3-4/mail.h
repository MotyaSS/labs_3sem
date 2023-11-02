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

typedef struct _mail {
  Address recieve_addr;
  double weight;
  String mail_id; // 14 chars
  String creation_time; // "dd:MM:yyyy hh:mm:ss"
} Mail;

typedef struct node {
  Mail* data;
  struct node* left;
  struct node* right;
} mail_bst_node;

typedef struct {
  mail_bst_node* root;
  int (* comp)(Mail*, Mail*);
} MailBST;

int bst_add(MailBST* bst, Mail* data);

typedef struct _post {
  Address* post_addr;
  MailBST mails;
} Post;

#endif