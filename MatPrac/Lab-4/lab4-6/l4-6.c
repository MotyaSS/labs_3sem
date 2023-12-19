#include "l4-6.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>


#define TABLE_INIT_SIZE 8

LNode* find_in_list(VarList* list, char* name) {
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->arr[i].name, name) == 0) {
            return &list->arr[i];
        }
    }
    if (list->size == list->cap) {
        LNode* temp = (LNode*) realloc(list->arr, sizeof(LNode) * list->cap * 2);
        if (temp == NULL) {
            return NULL;
        }
        list->arr = temp;
        list->cap *= 2;
    }
    list->arr[list->size].name = name;
    return &list->arr[list->size++];
}

int tnode_destr(TNode* node) {
    if (node == NULL) {
        return 1;
    }
    tnode_destr(node->left);
    tnode_destr(node->right);
    if (node->value) {
        free(node->value);
    }
    free(node);
    return 0;
}

//      STACK

TNode* stack_pop(stack* st) {
    if (st->top == NULL) {
        return NULL;
    }
    TNode* val = st->top->value;
    stack_node* new_top = st->top->next;
    free(st->top);
    st->top = new_top;
    return val;
}

TNode* stack_top(stack* st) {
    if (st->top == NULL) {
        return NULL;
    }
    return st->top->value;
}

int stack_push(stack* st, TNode* value) {
    stack_node* node = (stack_node*) malloc(sizeof(stack_node));
    if (!node) {
        return -1;
    }
    node->value = value;
    node->next = st->top;
    st->top = node;
    return 0;
}

int stack_destr(stack* st) {
    stack_node* node = st->top;
    while (node != NULL) {
        stack_node* next = node->next;
        tnode_destr(node->value);
        free(node);
        node = next;
    }
    return 0;
}


int read_operator(const char* str) {
    if (*str == 0) {
        return 0;
    }
    if (*str == '&' || *str == '|' || *str == '~' || *str == '=' || *str == '!' || *str == '?') {
        return 1;
    }
    if (str[1] == '>') {
        if (*str == '-' || *str == '+' || *str == '<') {
            return 2;
        }
    }
    return 0;
}

int get_priority(const char* str) {
    if (*str == 0) {
        return 0;
    }
    if (str[1] == 0) {
        switch (*str) {
            case '~':
                return 3;
            case '&':
            case '!':
            case '?':
                return 2;
            case '=':
            case '|':
                return 1;
            default:
                return 0;
        }
    }
    if (str[1] == '>' && str[2] == 0) {
        switch (*str) {
            case '+':
                return 2;
            case '-':
            case '<':
                return 1;
            default:
                return 0;
        }
    }
    return 0;
}

int read_name(const char* str) {
    const char* ptr = str;
    int cnt = 0;
    while (*ptr != 0 && isalpha(*ptr)) {
        ptr++;
        cnt++;
    }
    return cnt;
}

int read_num(const char* str) {
    char* ptr;
    strtoll(str, &ptr, 10);
    return (int) (ptr - str);
}

int variable_case_algo(stack* operationStack, stack* operandStack, char* name) {
    TNode* node = (TNode*) calloc(1, sizeof(TNode));
    if (!node) {
        free(name);
        stack_destr(operationStack);
        stack_destr(operandStack);
        return BAD_ALLOC;
    }
    node->value = name;
    stack_push(operandStack, node);
    return OK;
}

int operation_case_algo(stack* operationStack, stack* operandStack, char* name) {
    TNode* node = (TNode*) calloc(1, sizeof(TNode));
    if (!node) {
        free(name);
        stack_destr(operationStack);
        stack_destr(operandStack);
        return BAD_ALLOC;
    }
    node->value = name;

    while (stack_top(operationStack) != NULL &&
           get_priority(stack_top(operationStack)->value) >= get_priority(node->value)) {
        TNode* st_node = stack_pop(operationStack);
        TNode* op1 = stack_pop(operandStack);
        TNode* op2 = stack_pop(operandStack);
        if (!op2) {
            if (op1) {
                tnode_destr(op1);
            }
            tnode_destr(st_node);
            stack_destr(operationStack);
            stack_destr(operandStack);
            return UNCOMPUTABLE;
        }
        st_node->right = op1;
        st_node->left = op2;
        stack_push(operandStack, st_node);
    }
    stack_push(operationStack, node);
    return OK;
}

int build_tree(const char* expr, Tree* tree) {
    const char* ptr = expr;
    stack operandStack = {0};
    stack operationStack = {0};
    while (*ptr) {
        int ocnt, nacnt, nucnt;
        ocnt = read_operator(ptr), nacnt = read_name(ptr), nucnt = read_num(ptr);
        if (isspace(*ptr)) {
            continue;
        }


        else if (*ptr == '(') {
            char* name = malloc(sizeof(char) * 2);
            if (!name) {
                stack_destr(&operationStack);
                stack_destr(&operandStack);
                return BAD_ALLOC;
            }
            strcpy(name, "(");
            TNode* node = (TNode*) calloc(1, sizeof(TNode));
            if (!node) {
                free(name);
                stack_destr(&operationStack);
                stack_destr(&operandStack);
                return BAD_ALLOC;
            }
            node->value = name;
            ptr++;
            stack_push(&operationStack, node);
        }


        else if (*ptr == ')') {
            while (stack_top(&operationStack) != NULL && strcmp(stack_top(&operationStack)->value, "(") != 0) {
                TNode* st_node = stack_pop(&operationStack);
                TNode* op1 = stack_pop(&operandStack);
                TNode* op2 = stack_pop(&operandStack);
                if (!op2) {
                    if (op1) {
                        tnode_destr(op1);
                    }
                    tnode_destr(st_node);
                    stack_destr(&operationStack);
                    stack_destr(&operandStack);
                    return UNCOMPUTABLE;
                }
                st_node->right = op1;
                st_node->left = op2;
                stack_push(&operandStack, st_node);
            }
            if (stack_top(&operationStack) == NULL) {
                stack_destr(&operationStack);
                stack_destr(&operandStack);
                return UNCOMPUTABLE;
            }
            tnode_destr(stack_pop(&operationStack));
            ptr++;
        }


        else if (ocnt) { //operation
            char* name = malloc(sizeof(char) * (ocnt + 1));
            if (!name) {
                stack_destr(&operationStack);
                stack_destr(&operandStack);
                return BAD_ALLOC;
            }
            strncpy(name, ptr, ocnt);
            name[ocnt] = 0;
            ptr += ocnt;
            int code = operation_case_algo(&operationStack, &operandStack, name);
            if (code != OK) {
                return code;
            }
        }


        else if (nucnt) { //number
            char* name = malloc(sizeof(char) * (nucnt + 1));
            if (!name) {
                stack_destr(&operationStack);
                stack_destr(&operandStack);
                return BAD_ALLOC;
            }
            strncpy(name, ptr, nucnt);
            name[nucnt] = 0;
            if (strcmp(name, "0") != 0 && strcmp(name, "1") != 0) {
                stack_destr(&operationStack);
                stack_destr(&operandStack);
                return INV_NUMBER;
            }
            ptr += nucnt;
            int code = variable_case_algo(&operationStack, &operandStack, name);
            if (code != OK) {
                return code;
            }
        }


        else if (nacnt) { //variable name
            char* name = malloc(sizeof(char) * (nacnt + 1));
            if (!name) {
                stack_destr(&operationStack);
                stack_destr(&operandStack);
                return BAD_ALLOC;
            }
            strncpy(name, ptr, nacnt);
            name[nacnt] = 0;
            ptr += nacnt;
            int code = variable_case_algo(&operationStack, &operandStack, name);
            if (code != OK) {
                return code;
            }
        }


        else {
            stack_destr(&operationStack);
            stack_destr(&operandStack);
            return UNCOMPUTABLE;
        }
    }

    while (stack_top(&operationStack) != NULL) {
        TNode* st_node = stack_pop(&operationStack);
        TNode* op1 = stack_pop(&operandStack);
        TNode* op2 = stack_pop(&operandStack);
        if (!op2) {
            if (op1) {
                tnode_destr(op1);
            }
            tnode_destr(st_node);
            stack_destr(&operationStack);
            stack_destr(&operandStack);
            return UNCOMPUTABLE;
        }
        st_node->right = op1;
        st_node->left = op2;
        stack_push(&operandStack, st_node);
    }
    TNode* root = stack_pop(&operandStack);
    if (!root || stack_top(&operandStack) != NULL) {
        if (root) {
            tnode_destr(root);
        }
        stack_destr(&operandStack);
        return UNCOMPUTABLE;
    }
    tree->root = root;
    int code;
    if ((code = create_value_table(tree)) != OK) {
        tnode_destr(tree->root);
        return code;
    }
    return OK;
}

int foo(TNode* node, VarList* vars) {
    if (node == NULL) {
        return -1;
    }
    if (*node->value == '1' || *node->value == '0') {
        return 0;
    }
    if (read_operator(node->value) != 0) {
        int code;
        if ((code = foo(node->left, vars)) != 0) {
            return code;
        }
        if ((code = foo(node->right, vars)) != 0) {
            return code;
        }
        return 0;
    }
    node->cell = find_in_list(vars, node->value);
    if (node->cell == NULL) {
        return 1;
    }

    return 0;
}

int create_value_table(Tree* tree) {
    tree->vars.arr = malloc(sizeof(LNode) * TABLE_INIT_SIZE);
    if (!tree->vars.arr) {
        return BAD_ALLOC;
    }
    tree->vars.size = 0;
    tree->vars.cap = TABLE_INIT_SIZE;
    if (foo(tree->root, &tree->vars)) {
        return BAD_ALLOC;
    }
    return OK;
}