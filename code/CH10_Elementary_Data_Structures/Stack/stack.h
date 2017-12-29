#ifndef STACK_H
#define STACK_H 

#include <stdlib.h>
#include <assert.h>

/**
 * \file stack.h
 * \brief stack definition and basic operations
 * \author Firmin MARTIN 
 * \version 0.1
 * \date 28/12/2017
 */

/**
 * Abstract stack using dynamic array.
 * \struct stack_t
 */

typedef struct {
    size_t width;   /**< element size (in bytes) */
    int top;        /**< top element index */
    void** base;     /**< pointer to the dynamic array */
    int mem_size;   /**< width * mem_size bytes is reserved for the dynamic array */
} stack_t;

stack_t* stack_create(size_t width);
void stack_destruct(stack_t* s);
int stack_isempty(stack_t* s);
void* stack_pop(stack_t* s);
void stack_push(stack_t* s, void* e);

#endif /* ifndef STACK_H */
