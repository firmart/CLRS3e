
#include "bst.h"

int compare_int(const void* a, const void* b){
    int* pa = (int*) a;
    int* pb = (int*) b;
    return *pa - *pb;
}

int main(void) {
    static const int x[10] = {1, 2, 3, 7, 5, 6, 2, 8, 9, 10};
    int** px = malloc(10*sizeof(int*));
    for (int i = 0; i < 10; i++){
        px[i] = malloc(sizeof(int));
        *px[i] = x[i];
    }
    BST_t* bst = bst_create(sizeof(int), compare_int);
    for (int i = 0; i < 10; i++){
        bst_insert(bst, px[i]);
    }
    bst_inorder_walk_int(bst->root);
    BSTnode_t* min = bst_min(bst->root);
    printf("min := %d\n", (*(int*)(min->data)));
    BSTnode_t* max = bst_max(bst->root);
    printf("max := %d\n", (*(int*)(max->data)));
    BSTnode_t* min_succ = bst_succ(bst, min);
    printf("min_succ := %d\n", (*(int*)(min_succ->data)));
    BSTnode_t* max_pred = bst_pred(bst, max);
    printf("max_pred := %d\n", (*(int*)(max_pred->data)));
    bst_destruct(bst);
    free(px);
    return 0;
}

