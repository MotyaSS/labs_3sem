#include <stdio.h>
#include <stdlib.h>
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
    char* expr = "~a -> b&1";
    if ((code = build_tree(expr, &tree)) != OK) {
        printf("Err code:%d\n", code);
        return 1;
    }

    char filename[17];
    get_rand_name(filename, 16);
    FILE* out = fopen(filename, "w");
    if (!out) {
        printf("Unable to generate file\n");
        free(tree.vars.arr);
        tnode_destr(tree.root);
    }
    printf("created file %s\n", filename);


    print_tree(tree.root, 0);
    fprintf(out, "Expression is :\n %s\n", expr);
    print_table(out, &tree);

    fclose(out);
    free(tree.vars.arr);
    tnode_destr(tree.root);
    return 0;
}
