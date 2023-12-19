#define STR_INIT_SIZE 10

#include <ctype.h>
#include <math.h>
#include "l4_5.h"
#include "../../Lab-3/lab3-4/my_string.h"
#include "../../../my_flag_lib.h"
#include "string.h"


char *stack_pop(stack *st) {
    if (st->top == NULL) {
        return NULL;
    }
    char *val = st->top->value;
    stack_node *new_top = st->top->next;
    free(st->top);
    st->top = new_top;
    return val;
}

char *stack_top(stack *st) {
    if (st->top == NULL) {
        return NULL;
    }
    return st->top->value;
}

int stack_push(stack *st, char *value) {
    stack_node *node = (stack_node *) malloc(sizeof(stack_node));
    if (!node) {
        return -1;
    }
    node->value = value;
    node->next = st->top;
    st->top = node;
    return 0;
}

int stack_destr(stack *st) {
    stack_node *node = st->top;
    while (node != NULL) {
        stack_node *next = node->next;
        free(node);
        node = next;
    }
    return 0;
}

int clear_str_arr(char ***arr) {
    if (*arr == NULL) {
        return 1;
    }
    char **ptr = *arr;
    while (*ptr != NULL) {
        free(*ptr);
        ptr++;
    }
    free(*arr);
    arr = NULL;
    return 0;
}

eq_st_code split_expr(const char *src, char ***res) {
    int size = 1;
    *res = (char **) malloc(sizeof(char *) * size);
    (*res)[0] = NULL;
    while (*src) {
        int flag = 0;
        if (isspace(*src)) {
            src++;
            continue;
        }
        char *toadd = NULL;
        switch (*src) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^':
            case '(':
            case ')':
                flag = 1;
                toadd = malloc(sizeof(char) * 2);
                if (!toadd) {
                    clear_str_arr(res);
                    return EQ_BAD_ALLOC;
                }
                strncpy(toadd, src, 1);
                toadd[1] = 0;
                src++;
                break;
        }
        if (!flag) {
            char *end;
            strtoll(src, &end, 10);
            if (end != src) {
                //  Number
                flag = 1;
                toadd = malloc(sizeof(char) * (end - src + 1));
                if (!toadd) {
                    clear_str_arr(res);
                    return EQ_BAD_ALLOC;
                }
                strncpy(toadd, src, end - src);
                toadd[end - src] = 0;
                src = end;
            }
        }
        if (!flag) {
            clear_str_arr(res);
            return EQ_INV_OP;
        }
        char **temp = realloc(*res, sizeof(char *) * (++size));
        if (!temp) {
            clear_str_arr(res);
            return EQ_BAD_ALLOC;
        }
        *res = temp;
        (*res)[size - 2] = toadd;
        (*res)[size - 1] = NULL;
    }
    return EQ_OK;
}

int operation_priority(const char *str) {
    if (str == NULL || str[0] != 0 && str[1] != 0) {
        return -1;
    }
    if (*str == '(') {
        return 0;
    }
    if (*str == '+' || *str == '-') {
        return 1;
    }
    if (*str == '*' || *str == '/' || *str == '%') {
        return 2;
    }
    if (*str == '^') {
        return 3;
    }
    return -1;
}

eq_st_code convert_to_reversed(const char *src, char ***res) {
    char **split = NULL;
    eq_st_code code = split_expr(src, &split);
    if (code != EQ_OK) {
        return code;
    }
    char **ptr = split;
    stack st;
    st.top = NULL;
    *res = (char **) malloc(sizeof(char *));
    int res_size = 1;
    (*res)[0] = NULL;
    while (*ptr != NULL) {
        if (if_ll(*ptr)) {
            char **temp = realloc(*res, sizeof(char *) * (++res_size));
            if (!temp) {
                free(*res);
                clear_str_arr(&split);
                stack_destr(&st);
                return EQ_BAD_ALLOC;
            }
            *res = temp;
            (*res)[res_size - 2] = *ptr;
            (*res)[res_size - 1] = NULL;
        } else {
            if (strcmp("(", *ptr) == 0) {
                stack_push(&st, *ptr);
            } else if (strcmp(")", *ptr) == 0) {
                char *a;
                while ((a = stack_pop(&st)) != NULL && strcmp(a, "(") != 0) {
                    char **temp = realloc(*res, sizeof(char *) * (++res_size));
                    if (!temp) {
                        free(*res);
                        clear_str_arr(&split);
                        stack_destr(&st);
                        return EQ_BAD_ALLOC;
                    }
                    *res = temp;
                    (*res)[res_size - 2] = a;
                    (*res)[res_size - 1] = NULL;
                }

                if (a == NULL) {
                    free(*res);
                    clear_str_arr(&split);
                    stack_destr(&st);
                    return EQ_INV_BRACKET;
                }
                free(a);
            } else {
                int prior = operation_priority(*ptr);
                if (prior == -1) {
                    free(*res);
                    clear_str_arr(&split);
                    stack_destr(&st);
                    return EQ_INV_OP;
                }
                int top_prior = operation_priority(stack_top(&st));
                while (top_prior >= prior) {
                    char *a = stack_pop(&st);
                    char **temp = realloc(*res, sizeof(char *) * (++res_size));
                    if (!temp) {
                        free(*res);
                        clear_str_arr(&split);
                        stack_destr(&st);
                        return EQ_BAD_ALLOC;
                    }
                    *res = temp;
                    (*res)[res_size - 2] = a;
                    (*res)[res_size - 1] = NULL;
                    top_prior = operation_priority(stack_top(&st));
                }
                stack_push(&st, *ptr);
            }
        }
        ptr++;
    }
    char *a;
    while ((a = stack_pop(&st)) != NULL) {
        if (strcmp(a, "(") == 0) {
            free(*res);
            clear_str_arr(&split);
            stack_destr(&st);
            return EQ_INV_BRACKET;
        }
        char **temp = realloc(*res, sizeof(char *) * (++res_size));
        if (!temp) {
            free(*res);
            clear_str_arr(&split);
            stack_destr(&st);
            return EQ_BAD_ALLOC;
        }
        *res = temp;
        (*res)[res_size - 2] = a;
        (*res)[res_size - 1] = NULL;
    }

    return EQ_OK;
}

int print_eq_ok(FILE *stream, const char *expression, char **rev_exp, long long value) {
    fprintf(stream, "%s:\n", expression);
    while (*rev_exp != NULL) {
        fprintf(stream, "%s ", *rev_exp);
        rev_exp++;
    }
    fprintf(stream, "\n%d\n", value);
    fputc('\n', stream);
    return 0;
}

int print_eq_err(FILE *stream, const char *expression, eq_st_code code, int cnt) {
    fprintf(stream, "expression #%d: %s\n", cnt, expression);
    switch (code) {
        case EQ_BAD_ALLOC:
            fprintf(stream, " Bad Alloc during equation computing\n");
            break;
        case EQ_INV_BRACKET:
            fprintf(stream, " Bracket balance is off\n");
            break;
        case EQ_INV_OP:
            fprintf(stream, " Invalid operator found\n");
            break;
        case EQ_UNCOMPUTABLE:
            fprintf(stream, " Unable to compute\n");
            break;
    }
    return 0;
}

int print_st_code(FILE *stream, st_code code) {
    if (!stream) {
        return 1;
    }
    switch (code) {
        case OK:
            fprintf(stream, "All ok\n");
            break;
        case BAD_ALLOC:
            fprintf(stream, "Bad alloc\n");
            break;
        case INV_FILE:
            fprintf(stream, "Invalid file\n");
            break;
        case INV_ARGC:
            fprintf(stream, "Invalid argc\n");
            break;
    }
    return 0;
}

char *compute_op(const char *val1, const char *val2, const char *op) {
    char *result = NULL;

    long v1 = strtoll(val1, NULL, 10), v2 = strtoll(val2, NULL, 10), res;
    switch (*op) {
        case '+':
            res = v1 + v2;
            break;
        case '-':
            res = v1 - v2;
            break;
        case '*':
            res = v1 * v2;
            break;
        case '/':
            if (v2 == 0) {
                return NULL;
            }
            res = v1 / v2;
            break;
        case '%':
            res = v1 % v2;
            break;
        case '^':
            if (v2 < 0) {
                return NULL;
            }
            res = pow(v1, v2);
            break;
    }
    long long tres = res;
    int cnt = 1;
    if (tres < 0) {
        tres = -tres;
        cnt++;
    }
    while (tres != 0) {
        tres /= 10;
        cnt++;
    }
    result = (char *) malloc(sizeof(char) * cnt);
    sprintf(result, "%ld", res);
    return result;
}

int clear_stack(stack *st) {
    stack_node *node = st->top;
    while (node != NULL) {
        free(node->value);
        node = node->next;
    }
    stack_destr(st);
    return 0;
}

eq_st_code compute_exp(char **rev_exp, long long *result) {
    stack st = {0};
    char **ptr = rev_exp;
    stack tofree = {0};
    while (*ptr != NULL) {
        int priority = operation_priority(*ptr);
        if (priority == -1) {
            stack_push(&st, *ptr);
        } else {
            char *val2 = stack_pop(&st);
            char *val1 = stack_pop(&st);
            if (!val1 || !val2) {
                stack_destr(&st);
                return EQ_UNCOMPUTABLE;
            }
            char *res = compute_op(val1, val2, *ptr);
            if (res == NULL) {
                stack_destr(&st);
                return EQ_UNCOMPUTABLE;
            }
            stack_push(&st, res);
            stack_push(&tofree, res);
        }
        ptr++;
    }
    char *res = stack_pop(&st);
    if (res == NULL) {
        return EQ_UNCOMPUTABLE;
    }
    if (stack_top(&st) != NULL) {
        clear_stack(&tofree);
        stack_destr(&st);
        return EQ_UNCOMPUTABLE;
    }
    if (!if_ll(res)) {
        clear_stack(&tofree);
        return EQ_UNCOMPUTABLE;
    }
    *result = strtoll(res, NULL, 10);
    clear_stack(&tofree);
    return EQ_OK;
}

st_code compute_file(const char *filepath) {
    if (!filepath) {
        return INV_FILE;
    }
    FILE *stream = fopen(filepath, "r");
    if (!stream) {
        return INV_FILE;
    }
    String a;
    if (string_init(&a, STR_INIT_SIZE) != 0) {
        fclose(stream);
        return BAD_ALLOC;
    }

    FILE *errfile = NULL;
    int i = 0;
    while (!feof(stream)) {
        char **exp = NULL;
        switch (getline(&a, stream)) {
            case get_str_empty:
            case get_str_eof:
                break;
            case get_str_ok: {
                i++;
                eq_st_code code = convert_to_reversed(a._buf, &exp);
                if (code != EQ_OK) {
                    if (!errfile) {
                        char buf[BUFSIZ] = "";
                        snprintf(buf, sizeof(buf), "err_%s", filepath);
                        errfile = fopen(buf, "w");
                    }
                    if (errfile) {
                        print_eq_err(errfile, a._buf, code, i);
                    }
                } else {
                    long long value;
                    code = compute_exp(exp, &value);
                    if (code != EQ_OK) {
                        if (!errfile) {
                            char buf[BUFSIZ] = "";
                            snprintf(buf, sizeof(buf), "err_%s", filepath);
                            errfile = fopen(buf, "w");
                        }
                        if (errfile) {
                            print_eq_err(errfile, a._buf, code, i);
                        }
                    } else {
                        print_eq_ok(stdout, a._buf, exp, value);
                    }
                }

                break;
            }
            case get_str_bad_alloc:
                if (errfile) {
                    fclose(errfile);
                }
                fclose(stream);
                string_destr(&a);
                return BAD_ALLOC;
        }
    }

    fclose(stream);
    if (errfile) {
        fclose(errfile);
    }
    string_destr(&a);
    return OK;
}

st_code execute(int argc, char *argv[]) {
    if (argc < 2) {
        return INV_ARGC;
    }

    for (int i = 1; i < argc; i++) {
        int code = compute_file(argv[i]);
        if (code != OK) {
            printf("Error for file %s: ", argv[i]);
            print_st_code(stdout, code);
        }
    }
    return OK;
}