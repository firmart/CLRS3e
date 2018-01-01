#ifndef QUEUE_H
#define QUEUE_H 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * \file queue.h
 * \brief queue (using array) definition and basic operations
 * \author Firmin MARTIN 
 * \version 0.1
 * \date 28/12/2017
 */

/**
 * Abstract queue using array.
 * \struct queue_t
 * \todo \e base should'nt be accessible, see https://stackoverflow.com/questions/5368028/how-to-make-struct-members-private
 */

typedef struct {
    size_t width;   /**< element size (in bytes) */
    int front;      /**< front element index */
    int count;      /**< count element amount*/
    void** base;    /**< pointer to the array */
    int max_size;   /**< width * max_size bytes is reserved for the queue */
} queue_t;

queue_t* queue_create(size_t width, int max_size);
void queue_destruct(queue_t* q);
int queue_isempty(queue_t* q);
int queue_isfull(queue_t* q);
void* queue_dequeue(queue_t* q);
void queue_enqueue(queue_t* q, void* e);
void queue_int_print(queue_t* q);

#endif /* ifndef QUEUE_H */
