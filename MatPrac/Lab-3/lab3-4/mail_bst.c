#include "mail.h"

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
  if (bst->root == NULL) {
    node->data = data;
    bst->root = node;
    node->right = NULL;
    node->left = NULL;
    return 0;
  }
  if (_add(bst->root, node, bst->comp) != -1) {
    free(node);
    return 1;
  }
  return 0;
}