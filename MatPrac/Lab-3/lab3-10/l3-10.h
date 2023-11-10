#ifndef L3_10_H
#define L3_10_H

#include "../lab3-4/my_string.h"
#include <stdio.h>


typedef struct tree_node {
  char value;
  struct tree_node* parent;
  struct tree_node* brother;
  struct tree_node* child;
} tree_node;

tree_node* alloc_node(char value);

typedef struct {
  tree_node* root;
} Tree;

int tree_create(Tree* _tree, String* _string);
int print_tree(Tree* _tree, FILE* stream);
int tree_destroy(Tree* _tree);

#endif