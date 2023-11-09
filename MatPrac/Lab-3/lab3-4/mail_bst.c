#include "mail.h"

//  Initialization and Deletion

int bst_constr(MailBST* bst, int (* comp)(Mail*, Mail*)) {
  bst->root = NULL;
  bst->comp = comp;
  return 0;
}

int _destr(mail_bst_node* node) {
  if (node == NULL) {
    return 0;
  }
  _destr(node->left);
  _destr(node->right);
  mail_bst_node_destr(node);
  free(node);
  return 0;
}

int _only_free_destr(mail_bst_node* node) {
  if (node == NULL) {
    return 0;
  }
  _only_free_destr(node->left);
  _only_free_destr(node->right);
  free(node);
  return 0;
}

int bst_free_nodes(MailBST* bst) {
  _only_free_destr(bst->root);
  bst->root = NULL;
  bst->comp = NULL;
  return 0;
}

int bst_destr(MailBST* bst) {
  _destr(bst->root);
  bst->root = NULL;
  bst->comp = NULL;
  return 0;
}

int mail_bst_node_constr(mail_bst_node* node, Mail* data) {
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return 0;
}

int mail_bst_node_destr(mail_bst_node* node) {
  mail_destr(node->data);
  free(node->data);
  return 0;
}

//  Adding

int _add(mail_bst_node* root, mail_bst_node* new_node, int (* cmp)(Mail*, Mail*)) {
  int cmp_res = cmp(new_node->data, root->data);
  if (cmp_res > 0) {
    if (root->right == NULL) {
      root->right = new_node;
      return 0;
    }
    return _add(root->right, new_node, cmp);
  } else if (cmp_res < 0) {
    if (root->left == NULL) {
      root->left = new_node;
      return 0;
    }
    return _add(root->left, new_node, cmp);
  }
  return -1;
}

int bst_add(MailBST* bst, Mail* data) {
  mail_bst_node* node = (mail_bst_node*) malloc(sizeof(mail_bst_node));
  if (!node) {
    return -1;
  }
  mail_bst_node_constr(node, data);
  if (bst->root == NULL) {
    bst->root = node;
    return 0;
  }
  if (_add(bst->root, node, bst->comp) != 0) {
    free(node);
    return 1;
  }
  return 0;
}

Mail* _find_by_id(mail_bst_node* node, String const* id) {
  if (node == NULL) {
    return NULL;
  }
  if (string_is_equal(&node->data->mail_id, id)) {
    return node->data;
  }
  Mail* res;
  if ((res = _find_by_id(node->right, id)) || (res = _find_by_id(node->left, id))) {
    return res;
  }
  return NULL;
}

Mail* bst_find_id(MailBST* bst, String const* id) {
  return _find_by_id(bst->root, id);
}

//  Showing

void print_mail(Mail* mail, FILE* stream) {
  fprintf(stream, "cr. time: ");
  str_fprint(&mail->creation_time, stream);
  fputc('\n', stream);
  fprintf(stream, "re. time: ");
  str_fprint(&mail->recieve_time, stream);
  fputc('\n', stream);
  fprintf(stream, "index: ");
  str_fprint(&mail->recieve_addr.index, stream);
  fputc('\n', stream);
  fprintf(stream, "mail id: ");
  str_fprint(&mail->mail_id, stream);
  fputc('\n', stream);
}

int _show(mail_bst_node* node, FILE* stream, int* cnt) {
  if (node == NULL) {
    return -1;
  }
  _show(node->left, stream, cnt);
  printf("Mail %d:\n", ++(*cnt));
  print_mail(node->data, stream);
  _show(node->right, stream, cnt);
  return 0;
}

int bst_show(MailBST const* bst, FILE* stream) {
  int i = 0;
  _show(bst->root, stream, &i);
  return 0;
}