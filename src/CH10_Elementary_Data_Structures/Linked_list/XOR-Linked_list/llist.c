#include "llist.h"


//TODO: à compléter


/**
 * Given the size of each element and the list size, create a list.
 * \param width size of each element
 * \param max_size size of the list, max_size*width bytes will be reserved (definitively) for the list
 * \return a list initialized
 */

llist_t *llist_create(size_t width) {
    llist_t *l = malloc(sizeof(llist_t));
    assert(l);
    l->nil = malloc(sizeof(lnode_t));
    assert(l->nil);
    /* assume that the predecessor of l->nil have 0 as address, thus 0 XOR A = A */
    l->nil->np = l->nil;
    l->width = width;
    l->count = 0;
    return l;
}

/**
 * Free a list.
 * \param q a list
 */

void llist_destruct(llist_t *l) {
    lnode_t *pre = l->nil;
    lnode_t *cur = l->nil->np;
    lnode_t *tmp = NULL;

    while (cur) {
        tmp = pre;
        pre = cur;
        cur = cur->np ^ tmp;
        free(tmp->data);
        free(tmp);
    }

    free(l->nil);
    free(l);
}

/*
 * Given an index n, do a linear search on a list
 * \param l a list
 * \param n index
 * \return the node of index n
 */

lnode_t *llist_lsearch(llist_t *l, int n) {
    assert (n >= 0 || n < l->count) ;
    lnode_t *x = l->nil->next;

    for (int i = 0; i < n; i++) {
        x = x->next;
    }

    return x;
}

/*
 * Delete the node of index n
 * \param l a list
 * \param n index
 */

void llist_delete(llist_t *l, int n) {
    if (l->count == 0) {
        return ;
    }

    lnode_t *x =  llist_lsearch(l, n);
    x->prev->next = x->next;
    x->next->prev = x->prev;
    free(x->data);
    free(x);
    l->count--;
}

/*
 * Insert in the front of a given \p node a node \p x
 * \param node the node to prepend
 * \param x the node to insert
 */

static void llist_insert_ptr(lnode_t *node, lnode_t *x) {
    lnode_t *pn = node->prev;
    x->next = pn->next;
    pn->next->prev = x;
    pn->next = x;
    x->prev = pn;
}

/*
 * Given an index n, insert in the front of the node n
 * \param l a list
 * \param n index
 * \param e element
 * \return the new node of index n which be inserted
 */

lnode_t *llist_insert(llist_t *l, int n, void *e) {
    lnode_t *x = l->count == 0 ? l->nil : llist_lsearch(l, n);
    lnode_t *node = malloc(sizeof(lnode_t));
    assert(node);
    node->data = e;
    llist_insert_ptr(x, node);
    l->count++;
    return node;
}

/**
 * Print an int list
 */

void llist_int_print(llist_t *l) {
    printf("%d nodes : nil<->", l->count);
    lnode_t *x = l->nil->next;

    for (int i = 0; i < l->count; i++) {
        printf("[%d]<->", *((int *)x->data));
        x = x->next;
    }

    puts("nil");
}
