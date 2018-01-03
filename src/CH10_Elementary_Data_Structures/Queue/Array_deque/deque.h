#ifndef DEQUE_H
#define DEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * \file deque.h
 * \brief deque (using array) definition and basic operations
 * \author Firmin MARTIN 
 * \version 0.1
 * \date 28/12/2017
 */

/**
 * Abstract deque using array.
 * \struct deque_t
 * \todo \e base should'nt be accessible, see https://stackoverflow.com/questions/5368028/how-to-make-struct-members-private
 */

typedef struct {
    size_t width;   /**< element size (in bytes) */
    int front;      /**< front element index */
    int count;      /**< count element amount*/
    void** base;    /**< pointer to the array */
    int max_size;   /**< width * max_size bytes is reserved for the deque */
} deque_t;

deque_t* deque_create(size_t width, int max_size);
void deque_destruct(deque_t* q);
int deque_isempty(deque_t* q);
int deque_isfull(deque_t* q);
void* deque_dequeue(deque_t* q);
void* deque_dequeue_other_end(deque_t* q);
void deque_enqueue_other_end(deque_t* q, void* e);
void deque_enqueue(deque_t* q, void* e);
void deque_int_print(deque_t* q);

#endif /* ifndef deque_H*/
