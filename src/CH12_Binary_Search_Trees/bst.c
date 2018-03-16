#include <stdio.h>
#include <assert.h>

#include "bst.h"

BST_t *bst_create(size_t width, int (*compare)(const void *, const void *)) {
    BST_t *bst = malloc(sizeof(BST_t));
    assert(bst);
    bst->root = NULL;
    bst->count = 0;
    bst->height = 0;
    bst->width = width;
    bst->compare = compare;
    return bst;
}

static void bst_destruct_node(BSTnode_t *node) {
    if (!node) {
        return;
    }

    free(node->data);
    bst_destruct_node(node->left);
    bst_destruct_node(node->right);
    free(node);
}

void bst_destruct(BST_t *bst) {
    bst_destruct_node(bst->root);
    free(bst);
}

static BSTnode_t *bst_search_node(BSTnode_t *node, void *data, int (*compare)(const void *, const void *)) {
    if (node || !compare(data, node->data)) {
        return node;
    }

    if (compare(data, node->data) < 0) {
        return bst_search_node(node->left, data, compare);

    } else {
        return bst_search_node(node->right, data, compare);
    }
}

BSTnode_t *bst_search(BST_t *bst, void *data) {
    return bst_search_node(bst->root, data, bst->compare);
}

BSTnode_t *bst_iterative_search(BST_t *bst, void *data) {
    BSTnode_t *node = bst->root;

    while (node && !bst->compare(data, node->data)) {
        if (bst->compare(data, node->data) < 0) {
            node = node->left;

        } else {
            node = node->right;
        }
    }

    return node;
}

BSTnode_t *bst_min(BSTnode_t *node) {
    while (node->left) {
        node = node->left;
    }

    return node;
}


BSTnode_t *bst_max(BSTnode_t *node) {
    while (node->right) {
        node = node->right;
    }

    return node;
}

BSTnode_t *bst_succ(BST_t *bst, BSTnode_t *node) {
    if (node->right) {
        return bst_min(node->right);
    }

    BSTnode_t *x = node->parent;

    while (x && x->right && bst->compare(node->data, x->right->data) == 0) {
        node = x;
        x = x->parent;
    }

    return x;
}

BSTnode_t *bst_pred(BST_t *bst, BSTnode_t *node) {
    if (node->left) {
        return bst_max(node->left);
    }

    BSTnode_t *x = node->parent;

    while (x && x->left && bst->compare(node->data, x->left->data) == 0) {
        node = x;
        x = x->parent;
    }

    return x;
}

//TODO:update height and count
void static bst_insert_node(BST_t *bst, BSTnode_t *node) {
    BSTnode_t *x = bst->root, *y = NULL;

    while (x) {
        y = x;

        if (bst->compare(node->data, x->data) < 0) {
            x = x->left;

        } else {
            x = x->right;
        }
    }

    node->parent = y;

    if (!y) {
        bst->root = node;

    } else if (bst->compare(node->data, y->data) < 0) {
        y->left = node;

    } else {
        y->right = node;
    }
}

void bst_insert(BST_t* bst, void* data){
    BSTnode_t* node = malloc(sizeof(BSTnode_t)); 
    node->data = data;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    bst_insert_node(bst, node);
}

//TODO:update height and count
static void bst_transplant(BST_t* bst, BSTnode_t* u, BSTnode_t* v){
    if (!u->parent){
        bst->root = v;
    } else if (u == u->parent->left){
       u->parent->left = v; 
    } else {
       u->parent->right = v;
    }
    if (v){
        v->parent = u->parent;
    }
}

//TODO:update height and count
void bst_delete(BST_t* bst, BSTnode_t* node){
    if (!node->left){
        bst_transplant(bst, node, node->right); 
    } else if (!node->right){
        bst_transplant(bst, node, node->left); 
    } else {
        BSTnode_t* y = bst_min(node->right);
        if (y->parent != node){
            bst_transplant(bst, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        bst_transplant(bst, node, y);
        y->left = node->left;
        y->left->parent = y;
    }
}


//TODO:generalize this function
void bst_inorder_walk_int(BSTnode_t* node){
    if(!node) return;
    bst_inorder_walk_int(node->left);
    printf("%d\n", *((int*)(node->data)));
    bst_inorder_walk_int(node->right);
}

