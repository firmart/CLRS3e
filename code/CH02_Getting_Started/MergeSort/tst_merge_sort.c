#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "merge_sort.h"

#define DFLT_ARR_SIZE 20

void print_arr(int* arr,int size){
	for(int i = 0; i < size; i++)
		printf("%d ",arr[i]);
	puts("");
}


int main(int argc, char** argv){
    srand(time(NULL));

    long size = 0;

    if (argc > 1){
        size = atol(argv[1]);
    }
        
    size = size ? size : DFLT_ARR_SIZE;

    int* arr;

    arr = (int*)malloc(sizeof(int)*size);

    for(int i = 0; i < size; i++)
        arr[i] = rand()%500;

    print_arr(arr, size);    
	
	merge_sort(arr, 0, size - 1);

    print_arr(arr, size);    

    free(arr);
	return 0;
}
