#include <stdio.h>
#include <stdlib.h>
#include "l4-6.h"
#include "../../Lab-3/lab3-4/my_string.h"


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

int execute(int argc, char** argv) {
    if (argc != 2) {
        return 1;
    }

    FILE* in = fopen(argv[1], "r");
    if (!in) {
        return 2;
    }
    String a;
    if (string_init(&a, 16) != 0) {
        fclose(in);
        return 3;
    }

    if (getline(&a, in) != get_str_ok) {
        string_destr(&a);
        fclose(in);
        return 3;
    }
    fclose(in);

    Tree tree;
    int code;
    if ((code = build_tree(a._buf, &tree)) != OK) {
        string_destr(&a);
        printf("Err code: %d\n", code);
        return 4;
    }


    char filename[17];
    get_rand_name(filename, 16);
    FILE* out = fopen(filename, "w");
    if (!out) {
        printf("Unable to generate file\n");
        string_destr(&a);
        free(tree.vars.arr);
        tnode_destr(tree.root);
    }
    printf("created file %s\n", filename);


    print_tree(tree.root, 0);
    fprintf(out, "Expression is :\n %s\n", a._buf);
    string_destr(&a);
    print_table(out, &tree);
    fclose(out);


    free(tree.vars.arr);
    tnode_destr(tree.root);
    return 0;
}

int main(int argc, char* argv[]) {
    if(execute(argc, argv)){
        printf("something went wrong");
    }
}
