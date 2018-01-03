#include "llist.h"

/**
 * \file llist.c
 * \brief Singly linked list basic operations implementation
 * \author Firmin MARTIN
 * \version 0.1
 * \date 03/01/2018
 */

/**
 * Given the size of each element and the list size, create a list.
 * \param width size of each element
 * \param max_size size of the list, max_size*width bytes will be reserved (definitively) for the list
 * \return a list initialized
 */

llist_t* llist_create(size_t width) {
    llist_t* l = malloc(sizeof(llist_t));
    assert(l);
    l->nil = malloc(sizeof(lnode_t));
    assert(l->nil);
    l->nil->next = l->nil;
    l->width = width;
    l->count = 0;
    return l;
}

/**
 * Free a list.
 * \param q a list
 */

void llist_destruct(llist_t* l) {
    lnode_t* x = l->nil->next, *p;
    while(x != l->nil) {
        p = x;
        x = x->next;
        free(p->data);
        free(p);
    }
    free(l->nil);
    free(l);
}

/*
 * Given an index n, do a linear search on a list, return the node.
 * If n == -1, return sentinel node.
 * \param l a list
 * \param n index
 * \return the node of index n
 */

lnode_t* llist_lsearch(llist_t* l, int n) {
    assert (n >= -1 || n < l->count) ;
    lnode_t* x = l->nil;
    for(int i = -1; i < n; i++) {
        x = x->next;
    }
    return x;
}

/*
 * Delete the node of index n
 * \param l a list
 * \param n index
 */

void llist_delete(llist_t* l, int n) {
    if (l->count == 0) return ;
    /* get the previous node */
    lnode_t* x =  llist_lsearch(l, n - 1);
    lnode_t* p = x->next;
    x->next = p->next;
    free(p->data);
    free(p);
    l->count--;
}

/*
 * Insert a node \e x after a given node \e node
 * \param node the node to prepend
 * \param x the node to insert 
 */

static void llist_insert_ptr(lnode_t* before, lnode_t* after) {
    after->next = before->next;
    before->next = after;
}

/*
 * Given an index n, insert in the front of the node n
 * \param l a list
 * \param n index
 * \param e element
 * \return the new node of index n which be inserted
 */

lnode_t* llist_insert(llist_t* l, int n, void* e) {
    /* get the previous node */
    lnode_t* x =  llist_lsearch(l, n - 1);
    lnode_t* node = malloc(sizeof(lnode_t));
    assert(node);
    node->data = e;
    llist_insert_ptr(x, node);
    l->count++;
    return node;
}

/**
 * Print an int list
 */

void llist_int_print(llist_t* l) {
    printf("%d nodes : nil->", l->count);
    lnode_t* x = l->nil->next;
    for(int i = 0; i < l->count; i++) {
        printf("[%d]->", *((int*)x->data));
        x = x->next;
    }
    puts("nil");
}
