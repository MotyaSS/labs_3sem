#ifndef L3_9_H
#define L3_9_H

//структура не имеет сами value, они создаются вне дерева, здесь они просто обитают
//тем не менее для простоты при удалении дерева все value чистятся, с этим осторожнее

typedef struct TNode {
    char* value;
    struct TNode* left;
    struct Tnode* right;
} TNode;

typedef struct {
    TNode* root;
    int (* cmp)(const char* name1, const char* name2);
} BST;

int bst_init(BST* tree);
int bst_destr(BST* tree);


//вернет 0 если элемент добавлен, 1 если элемент был и его инкрементировали, -1 если ошибка
//если вернулась 1 не забыть почистить value вне функции
int bst_add(BST* tree, char* value);


#endif