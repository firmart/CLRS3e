/**
 * \file stack.c
 * \brief stack's basic operations implementation (using dynamic array)
 * \author Firmin MARTIN 
 * \version 0.1
 * \date 28/12/2017
 */

#include "stack.h"

/**
 * Determinate the emptiness of a stack.
 * \param s stack
 * \return 1 if the stack s is empty, 0 otherwise. 
 */

int stack_isempty(stack_t* s) {
    return s->top == -1;
}

/**
 * Push an element e into the stack s.
 * \param s stack
 * \param e element which be pushed
 */

void stack_push(stack_t* s, void* e) {
    s->top++;
    if (s->top == s->mem_size) {
        void** newptr = realloc(s->base, sizeof(void*) * (s->mem_size + 10));
        assert(newptr);
        s->base = newptr;
        s->mem_size += 10;
    }
    s->base[s->top] = e;
}

/**
 * Pop out an element from the stack s.
 * \param s stack
 * \return an element
 */

void* stack_pop(stack_t* s) {
    if (stack_isempty(s)) return NULL;
    s->top--;
    return s->base[s->top + 1];
}

/**
 * Given the size of each element, create a stack 
 * 10 * sizeof(void*) bytes is reserved by default.
 * \param width size of each element
 * \return a stack initialized
 */

stack_t* stack_create(size_t width) {
    stack_t* s = malloc(sizeof(stack_t));
    assert(s);
    s->width = width;
    s->mem_size = 10;
    s->base = (void**) malloc(sizeof(void*) * s->mem_size);
    assert(s->base);
    s->top = -1;
    return s;
}

/**
 * Free a stack.
 * \param s a stack
 */

void stack_destruct(stack_t* s) {
    free(s->base);
    free(s);
}



