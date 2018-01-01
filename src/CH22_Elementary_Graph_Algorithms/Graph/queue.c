/**
 * \file queue.c
 * \brief queue's basic operations implementation (using dynamic array)
 * \author Firmin MARTIN
 * \version 0.1
 * \date 28/12/2017
 */

#include "queue.h"

/**
 * Determinate the emptiness of a queue.
 * \param s queue
 * \return 1 if the queue s is empty, 0 otherwise. 
 */

int queue_isempty(queue_t* q) {
    return q->count == 0;
}

/**
 * Determinate the fullness of a queue.
 * \param s queue
 * \return 1 if the queue s is full, 0 otherwise. 
 */

int queue_isfull(queue_t* q) {
    return q->count == q->max_size;
}

/**
 * Enqueue an element e into the queue q.
 * \param q queue
 * \param e element which be enqueued 
 */

void queue_enqueue(queue_t* q, void* e) {
    if(queue_isfull(q)) {
        fprintf(stderr, "The queue is full : failed to enqueue.\n");
        return;
    }
    q->base[q->front] = e;
    if (q->front == q->max_size - 1) q->front = 0;
    else q->front++;
    q->count = q->count + 1;
}

/**
 * Dequeue an element from the queue s.
 * \param q queue
 * \return an element or NULL if the queue is empty
 */

void* queue_dequeue(queue_t* q) {
    if(queue_isempty(q)) {
        fprintf(stderr, "The queue is empty : failed to dequeue.\n");
        return NULL;
    }
    void* e = q->base[(q->front - q->count + q->max_size)%q->max_size];
    q->count--;
    return e;
}

/**
 * Given the size of each element and the queue size, create a queue.
 * \param width size of each element
 * \param max_size size of the queue, max_size*width bytes will be reserved (definitively) for the queue
 * \return a queue initialized
 */

queue_t* queue_create(size_t width, int max_size) {
    queue_t* q = malloc(sizeof(queue_t));
    assert(q);
    q->width = width;
    q->max_size = max_size ;
    q->base = (void**) calloc(q->max_size, sizeof(void*));
    assert(q->base);
    q->front = 0;
    q->count = 0;
    return q;
}

/**
 * Free a queue.
 * \param q a queue
 */

void queue_destruct(queue_t* q) {
    free(q->base);
    free(q);
}



