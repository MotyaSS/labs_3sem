#ifndef L4_6_H
#define L4_6_H

typedef enum {
    OK,
    BAD_ALLOC,
    INV_NUMBER,
    UNCOMPUTABLE,
    INV_FILE
} st_code;


typedef struct {
    char* name;
    int value;
} LNode;
typedef struct {
    LNode* arr;
    int cap;
    int size;
} VarList; // Здесь хранятся все переменнные, после построения дерева происходит перебор значений

LNode* find_in_list(VarList* list, char* name);


typedef struct TNode {
    char* value; //if value is "0" or "1" - its constant
    LNode* cell; // Отсылается на место в списке переменных для перебора значений и построения таблицы
    //if NULL - TNode is either an operator or a constant
    struct TNode* left;
    struct TNode* right;
} TNode;
int tnode_destr(TNode* node);
typedef struct {
    TNode* root;
    VarList vars;
} Tree;



typedef struct stack_node {
    TNode* value;
    struct stack_node* next;
} stack_node;
typedef struct {
    stack_node* top;
} stack;
TNode* stack_pop(stack* st);
TNode* stack_top(stack* st);
int stack_push(stack* st, TNode* value);
int stack_destr(stack* st);


int read_operator(const char* str); //returns count of keys read from str
int read_name(const char* str); //returns count of keys read from str
int read_num(const char* str); //returns count of keys read from str

int create_value_table(Tree* tree);
int build_tree(const char* expr, Tree* tree);

int get_rand_name(char** name);

#endif