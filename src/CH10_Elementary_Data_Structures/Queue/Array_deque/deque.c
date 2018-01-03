/**
 * \file deque.c
 * \brief deque's basic operations implementation (using array)
 * \author Firmin MARTIN
 * \version 0.1
 * \date 28/12/2017
 */

#include "deque.h"

/**
 * Determinate the emptiness of a deque.
 * \param s deque
 * \return 1 if the deque s is empty, 0 otherwise.
 */

int deque_isempty(deque_t* q) {
    return q->count == 0;
}

/**
 * Determinate the fullness of a deque.
 * \param s deque
 * \return 1 if the deque s is full, 0 otherwise.
 */

int deque_isfull(deque_t* q) {
    return q->count == q->max_size;
}

/**
 * Enqueue an element e into the deque q.
 * \param q deque
 * \param e element which be endequed
 */

void deque_enqueue(deque_t* q, void* e) {
    if(deque_isfull(q)) {
        fprintf(stderr, "The deque is full : failed to enqueue.\n");
        return;
    }
    q->base[q->front] = e;
    q->count++;
    q->front = (q->front + 1) % q->max_size;
}

/**
 * Enqueue an element e into the deque q at the other end.
 * \param q deque
 * \param e element which be endequed
 */

void deque_enqueue_other_end(deque_t* q, void* e) {
    if(deque_isfull(q)) {
        fprintf(stderr, "The deque is full : failed to enqueue.\n");
        return;
    } q->base[(q->front - (q->count + 1) + q->max_size) % q->max_size] = e;
    q->count++;
}

/**
 * Dequeue an element from the queue s.
 * \param q queue
 * \return an element or NULL if the queue is empty
 */

void* deque_dequeue(deque_t* q) {
    if(deque_isempty(q)) {
        fprintf(stderr, "The deque is empty : failed to dequeue.\n");
        return NULL;
    }
    void* e = q->base[(q->front - q->count + q->max_size) % q->max_size];
    q->count--;
    return e;
}

/**
 * Dequeue an element from the deque s at the other end.
 * \param q deque
 * \return an element or NULL if the deque is empty
 */

void* deque_dequeue_other_end(deque_t* q) {
    if(deque_isempty(q)) {
        fprintf(stderr, "The deque is empty : failed to dequeue.\n");
        return NULL;
    }
    q->front = (q->front - 1 + q->max_size) % q->max_size;
    void* e = q->base[q->front];
    q->count--;
    return e;
}

/**
 * Given the size of each element and the deque size, create a deque.
 * \param width size of each element
 * \param max_size size of the deque, max_size*width bytes will be reserved (definitively) for the deque
 * \return a deque initialized
 */

deque_t* deque_create(size_t width, int max_size) {
    deque_t* q = malloc(sizeof(deque_t));
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
 * Free a deque.
 * \param q a deque
 */

void deque_destruct(deque_t* q) {
    for(int i=0; i<q->max_size;i++){
        free(q->base[i]);
    }
    free(q->base);
    free(q);
}

/**
 * Print an int deque
 */

void deque_int_print(deque_t* q) {
    for(int i = 0; i < q->max_size; i++) {
        if ((q->front - i + q->max_size) % q->max_size <= q->count && i != q->front)
            printf("[%d]", *((int*)q->base[i]));
        else
            printf("[]");
    }
    puts("");
}

