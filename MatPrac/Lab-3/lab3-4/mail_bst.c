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

int bst_destr(MailBST* bst) {
  _destr(bst->root);
  bst->root = NULL;
  bst->comp = NULL;
  return 0;
}

int mail_bst_node_constr(mail_bst_node* node, Mail const* data) {
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

int bst_add(MailBST* bst, Mail const* data) {
  mail_bst_node* node = (mail_bst_node*) malloc(sizeof(mail_bst_node));
  if (!node) {
    return -1;
  }
  mail_bst_node_constr(node, data);
  if (bst->root == NULL) {
    bst->root = node;
    return 0;
  }
  if (_add(bst->root, node, bst->comp) == -1) {
    free(node);
    return 1;
  }
  return 0;
}

//  Showing

void print_mail(Mail* mail, FILE* stream) {
  str_fprint(&mail->recieve_addr.index, stream);
  fputc(':', stream);
  str_fprint(&mail->mail_id, stream);
  fputc('\n', stream);
}

int _show(mail_bst_node* node, FILE* stream) {
  if (node == NULL) {
    return -1;
  }
  _show(node->left, stream);
  print_mail(node->data, stream);
  _show(node->right, stream);
  return 0;
}

int bst_show(MailBST const* bst, FILE* stream) {
  _show(bst->root, stream);
  return 0;
}