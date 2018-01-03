#ifndef LLIST_H
#define LLIST_H 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * \file llist.h
 * \brief Singly linked list definition and basic operations
 * \author Firmin MARTIN 
 * \version 0.1
 * \date 03/01/2018
 */

typedef struct lnode_t {
    void* data;           /**< data pointer */
    struct lnode_t* next; /**< next node */
} lnode_t;

typedef struct llist_t {
    size_t width;   /**< element size (in bytes) */
    lnode_t* nil;   /**< sentinel (dummy node)   */
    int count;      /**< count element amount*/
} llist_t;

llist_t*  llist_create(size_t width);
void  llist_destruct(llist_t* l);
lnode_t*  llist_insert(llist_t* l, int n, void* e);
void llist_delete(llist_t* l, int n);
void  llist_int_print(llist_t* l);
lnode_t*  llist_lsearch(llist_t* l, int n);

#endif /* ifndef LLIST_H */
