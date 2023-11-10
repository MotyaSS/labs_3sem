#include "l3-10.h"

#include <stdio.h>
#include <stdbool.h>


tree_node* alloc_node(char value) {
  tree_node* temp = (tree_node*) malloc(sizeof(tree_node));
  if (temp == NULL) {
    return temp;
  }
  temp->value = value;
  temp->child = NULL;
  temp->brother = NULL;
  temp->parent = NULL;
  return temp;
}

void _print_tree(tree_node* node, FILE* stream, int depth) {
  if (node == NULL) {
    return;
  }

  for (int i = 0; i < depth; i++) {
    fprintf(stream, "  ");
  }

  fprintf(stream, "%c\n", node->value);
  _print_tree(node->child, stream, depth + 1);
  _print_tree(node->brother, stream, depth);
}

int print_tree(Tree* _tree, FILE* stream) {
  if (stream == NULL) {
    return -1;
  }
  if (_tree == NULL) {
    return -2;
  }
  _print_tree(_tree->root, stream, 0);
  return 0;
}

int add_child(tree_node* node, tree_node* to_add) {
  if (node->child != NULL) {
    return -1;
  }
  node->child = to_add;
  to_add->parent = node;
  return 0;
}

int add_brother(tree_node* node, tree_node* to_add) {
  if (node->brother != NULL) {
    return -1;
  }
  node->brother = to_add;
  to_add->parent = node->parent;
  return 0;
}

int tree_create(Tree* _tree, String* _string) {
  if (_tree == NULL) {
    return -1;
  }
  if (_string == NULL) {
    return -2;
  }
  if (string_is_empty(_string)) {
    return -3;
  }
  char* ptr = _string->_buf;
  size_t size = _string->_size;
  tree_node* cur_node;
  bool if_next_child = false;
  bool if_first = true;
  for (int i = 0; i < size; i++) {
    switch (ptr[i]) {
      case ' ':
      case ',':
        break;
      case '(':
        if (if_next_child) {
          return -6;
        }
        if_next_child = true;
        break;
      case ')':
        if(cur_node->parent == NULL){
          return -7;
        }
        cur_node = cur_node->parent;
        break;
      default: {
        tree_node* new_node;
        if ((new_node = alloc_node(ptr[i])) == NULL) {
          return 1;
        }
        if (if_first) {
          _tree->root = new_node;
          cur_node = new_node;
          if_first = false;
          break;
        }
        if (if_next_child) {
          if (add_child(cur_node, new_node) != 0) {
            return -4;
          }
          cur_node = cur_node->child;
          if_next_child = false;
        } else {
          if (add_brother(cur_node, new_node)) {
            return -5;
          }
          cur_node = cur_node->brother;
        }
      }
    }
  }
  return 0;
}

int _delete_node(tree_node* node) {
  if (node == NULL) {
    return 0;
  }
  _delete_node(node->brother);
  _delete_node(node->child);
  free(node);
  return 0;
}

int tree_destroy(Tree* _tree) {
  _delete_node(_tree->root);
  _tree->root = NULL;
  return 0;
}