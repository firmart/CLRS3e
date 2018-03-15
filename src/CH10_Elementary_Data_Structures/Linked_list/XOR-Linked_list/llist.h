#ifndef XORLIST_H
#define XORLIST_H 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * \file xorlist.h
 * \brief XOR linked list definition and basic operations
 * \author Firmin MARTIN 
 * \version 0.1
 * \date 29/01/2018
 */

typedef struct lnode_t {
    void* data;           /**< data pointer */
    struct lnode_t* np; /**< XOR of next/previous node's pointer  */
} lnode_t;

typedef struct xorlist_t {
    size_t width;   /**< element size (in bytes) */
    lnode_t* nil;   /**< sentinel (dummy node)   */
    int count;      /**< count element amount*/
} xorlist_t;

xorlist_t*  xorlist_create(size_t width);
void  xorlist_destruct(xorlist_t* l);
lnode_t*  xorlist_insert(xorlist_t* l, int n, void* e);
void xorlist_delete(xorlist_t* l, int n);
void  xorlist_int_print(xorlist_t* l);
lnode_t*  xorlist_lsearch(xorlist_t* l, int n);

#endif /* ifndef XORLIST_H */
