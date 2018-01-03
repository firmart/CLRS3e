#include <stdio.h>

#include "queue.h"

int main() {
    queue_t* q = queue_create(sizeof(int), 10);
    int e1 = 5;
    int e2 = 6;
    int e3 = 7;
    int* e;
    printf("enqueue e1=%d\n", e1);queue_enqueue(q, &e1);
    printf("enqueue e2=%d\n", e2);queue_enqueue(q, &e2);
    printf("enqueue e3=%d\n", e3);queue_enqueue(q, &e3);
    e = queue_dequeue(q); printf("dequeue e=%d\n", *e);
    e = queue_dequeue(q); printf("dequeue e=%d\n", *e);
    e = queue_dequeue(q); printf("dequeue e=%d\n", *e);
    queue_destruct(q);

    queue_t* q2 = queue_create(sizeof(char), 3);
    char c1 = 's';
    char c2 = 'u';
    char c3 = 'v';
    char c4 = 'w';
    char c5 = 'x';
    char c6 = 'y';
    char* c;
    printf("enqueue c1='%c'\n", c1);queue_enqueue(q2, &c1);
    printf("enqueue c2='%c'\n", c2);queue_enqueue(q2, &c2);
    printf("enqueue c3='%c'\n", c3);queue_enqueue(q2, &c3);
    c = queue_dequeue(q2); printf("dequeue c='%c'\n", *c);
    c = queue_dequeue(q2); printf("dequeue c='%c'\n", *c);
    c = queue_dequeue(q2); printf("dequeue c='%c'\n", *c);
    printf("enqueue c4='%c'\n", c4);queue_enqueue(q2, &c4);
    printf("enqueue c5='%c'\n", c5);queue_enqueue(q2, &c5);
    printf("enqueue c6='%c'\n", c6);queue_enqueue(q2, &c6);
    c = queue_dequeue(q2); printf("dequeue c='%c'\n", *c);
    c = queue_dequeue(q2); printf("dequeue c='%c'\n", *c);
    c = queue_dequeue(q2); printf("dequeue c='%c'\n", *c);
    queue_destruct(q2);
    return 0;
}
