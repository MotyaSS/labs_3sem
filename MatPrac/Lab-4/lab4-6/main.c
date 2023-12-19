#include <stdio.h>
#include "l4-6.h"


int print_tree(TNode* node, int level) {
    if (node) {
        print_tree(node->right, level + 1);
        for (int i = 0; i < level; i++) {
            printf("\t");
        }
        printf("%s\n", node->value);
        print_tree(node->left, level + 1);
    }
    return 0;
}

int main() {
    Tree tree;
    int code;
    if ((code = build_tree("(1->a)&(a->b|b)", &tree)) == OK) {
        print_tree(tree.root, 0);
    }
    else{
        printf("%d", code);
    }
}
