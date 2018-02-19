#include <stdio.h>
#include "llist.h"


static int* int2ptr(int i) {
    int* ptr = malloc(sizeof(int));
    assert(ptr);
    *ptr = i;
    return ptr;
}

int main(int argc, char *argv[]) {
    llist_t* l = llist_create(sizeof(int));
    for(int i = 0; i < 10; i++){
        llist_insert(l, 0, int2ptr(i));
    }
    llist_int_print(l);
    llist_insert(l, 5, int2ptr(777));
    llist_int_print(l);
    llist_delete(l, 5);
    llist_int_print(l);
    llist_delete(l, 0);
    llist_int_print(l);
    llist_delete(l, 0);
    llist_int_print(l);
    llist_delete(l, 0);
    llist_int_print(l);
    llist_delete(l, 0);
    llist_int_print(l);
    llist_delete(l, 0);
    llist_int_print(l);
    llist_delete(l, 0);
    llist_int_print(l);
    llist_delete(l, 0);
    llist_int_print(l);
    llist_destruct(l);
    return 0;
}
