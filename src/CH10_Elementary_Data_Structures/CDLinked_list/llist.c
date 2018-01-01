#include "llist.h"

llist_t* llist_create(size_t width) {
    llist_t* l = malloc(sizeof(llist_t));
    assert(l);
    l->nil = malloc(sizeof(lnode_t));
    assert(l->nil);
    l->nil->prev = l->nil;
    l->nil->next = l->nil;
    l->width = width;
    l->count = 0;
    return l;
}

void llist_destruct(llist_t* l) {
    lnode_t* x = l->nil->next;
    while(x != l->nil) {
        free(x->data);
        x = x->next;
        free(x->prev);
    }
    free(l->nil);
    free(l);
}

lnode_t* llist_lsearch(llist_t* l, int n) {
    assert (n >= 0 || n < l->count) ;
    lnode_t* x = l->nil->next;
    for(int i = 0; i < n; i++) {
        x = x->next;
    }
    return x;
}

void llist_delete(llist_t* l, int n) {
    if (l->count == 0) return ;
    lnode_t* x =  llist_lsearch(l, n);
    x->prev->next = x->next;
    x->next->prev = x->prev;
    free(x->data);
    free(x);
    l->count--;
}

static void llist_insert_ptr(lnode_t* node, lnode_t* x) {
    lnode_t* pn = node->prev;
    x->next = pn->next;
    pn->next->prev = x;
    pn->next = x;
    x->prev = pn;
}

lnode_t* llist_insert(llist_t* l, int n, void* e) {
    lnode_t* x = l->count == 0 ? l->nil : llist_lsearch(l, n);
    lnode_t* node = malloc(sizeof(lnode_t));
    assert(node);
    node->data = e;
    llist_insert_ptr(x, node);
    l->count++;
    return node;
}

void llist_int_print(llist_t* l) {
    printf("%d nodes : nil<->", l->count);
    lnode_t* x = l->nil->next;
    for(int i = 0; i < l->count; i++) {
        printf("[%d]<->", *((int*)x->data));
        x = x->next;
    }
    puts("nil");
}
