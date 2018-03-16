#ifndef BST_H
#define BST_H

/**
 * \file bst.h
 * \brief binary search tree definition and basic operations
 * \author Firmin MARTIN 
 * \version 0.1
 * \date 16/03/2018
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct BSTnode_t {
    struct BSTnode_t* parent;     /**< parent node */
    struct BSTnode_t* left;     /**< left child */
    struct BSTnode_t* right;     /**< right child */
    void* data;          /**< data pointer */
}BSTnode_t;

typedef struct BST_t {
    size_t width;   /**< element size (in bytes) */
    BSTnode_t* root;  /**< root node */
    int count;      /**< count element amount*/
    int height;     /**< tree height*/
    int (*compare)(const void *, const void *);
}BST_t;

BST_t* bst_create(size_t width, int (*compare)(const void *, const void *));
void bst_destruct(BST_t *bst);
void bst_insert(BST_t *bst, void *data);
void bst_delete(BST_t* bst, BSTnode_t* node);
BSTnode_t* bst_search(BST_t *bst, void *data);
BSTnode_t* bst_iterative_search(BST_t *bst, void *data);
BSTnode_t* bst_max(BSTnode_t *node);
BSTnode_t* bst_min(BSTnode_t *node);
BSTnode_t* bst_succ(BST_t *bst, BSTnode_t *node);
BSTnode_t* bst_pred(BST_t *bst, BSTnode_t *node) ;
void bst_inorder_walk_int(BSTnode_t* node);

#endif
