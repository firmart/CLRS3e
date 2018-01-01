#include <stdio.h>

#include "stack.h"

int main() {
    stack_t* s = stack_create(sizeof(int));
    int e1 = 5;
    int e2 = 6;
    int e3 = 7;
    int* e;
    printf("push e1=%d\n", e1);stack_push(s, &e1);
    printf("push e2=%d\n", e2);stack_push(s, &e2);
    printf("push e3=%d\n", e3);stack_push(s, &e3);
    e = stack_pop(s); printf("pop e=%d\n", *e);
    e = stack_pop(s); printf("pop e=%d\n", *e);
    e = stack_pop(s); printf("pop e=%d\n", *e);
    stack_destruct(s);

    stack_t* s2 = stack_create(sizeof(char));
    char c1 = 's';
    char c2 = 'u';
    char c3 = 'v';
    char* c;
    printf("push c1='%c'\n", c1);stack_push(s, &c1);
    printf("push c2='%c'\n", c2);stack_push(s, &c2);
    printf("push c3='%c'\n", c3);stack_push(s, &c3);
    c = stack_pop(s2); printf("pop c='%c'\n", *c);
    c = stack_pop(s2); printf("pop c='%c'\n", *c);
    c = stack_pop(s2); printf("pop c='%c'\n", *c);
    stack_destruct(s2);
    return 0;
}
