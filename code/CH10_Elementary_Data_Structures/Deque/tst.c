#include <stdio.h>

#include "deque.h"

int main() {
    deque_t* q = deque_create(sizeof(int), 10);
    int e1 = 5;
    int e2 = 6;
    int e3 = 7;
    int e4 = 8;
    int e5 = 9;
    int e6 = 10;
    int* e;
    printf("enqueue e1=%d\n", e1);deque_enqueue(q, &e1);deque_int_print(q);
    printf("enqueue e2=%d\n", e2);deque_enqueue(q, &e2);deque_int_print(q);
    printf("enqueue e3=%d\n", e3);deque_enqueue(q, &e3);deque_int_print(q);
    e = deque_dequeue(q);printf("dequeue e=%d\n", *e);deque_int_print(q);
    printf("enqueue at the other end e4=%d\n", e4);deque_enqueue_other_end(q, &e4);deque_int_print(q);
    printf("enqueue at the other end e5=%d\n", e5);deque_enqueue_other_end(q, &e5);deque_int_print(q);
    printf("enqueue at the other end e6=%d\n", e6);deque_enqueue_other_end(q, &e6);deque_int_print(q);
    e = deque_dequeue(q);printf("dequeue e=%d\n", *e);deque_int_print(q);
    e = deque_dequeue_other_end(q);printf("dequeue at the other end e=%d\n", *e);deque_int_print(q);
    e = deque_dequeue_other_end(q);printf("dequeue at the other end e=%d\n", *e);deque_int_print(q);
    deque_destruct(q);

//    deque_t* q2 = deque_create(sizeof(char), 3);
//    char c1 = 's';
//    char c2 = 'u';
//    char c3 = 'v';
//    char c4 = 'w';
//    char c5 = 'x';
//    char c6 = 'y';
//    char* c;
//    printf("enqueue c1='%c'\n", c1);deque_enqueue(q2, &c1);
//    printf("enqueue c2='%c'\n", c2);deque_enqueue(q2, &c2);
//    printf("enqueue c3='%c'\n", c3);deque_enqueue(q2, &c3);
//    c = deque_dequeue(q2); printf("dequeue c='%c'\n", *c);
//    c = deque_dequeue(q2); printf("dequeue c='%c'\n", *c);
//    c = deque_dequeue(q2); printf("dequeue c='%c'\n", *c);
//    printf("enqueue c4='%c'\n", c4);deque_enqueue(q2, &c4);
//    printf("enqueue c5='%c'\n", c5);deque_enqueue(q2, &c5);
//    printf("enqueue c6='%c'\n", c6);deque_enqueue(q2, &c6);
//    c = deque_dequeue(q2); printf("dequeue c='%c'\n", *c);
//    c = deque_dequeue(q2); printf("dequeue c='%c'\n", *c);
//    c = deque_dequeue(q2); printf("dequeue c='%c'\n", *c);
//    deque_destruct(q2);
    return 0;
}
