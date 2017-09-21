#include <stdlib.h>
#include <string.h>

#include "merge_sort.h"

int merge_sort(int* arr, int low, int high){
	if (low < high){
		int q = (int)((high + low) / 2);
		merge_sort(arr, low, q);
		merge_sort(arr, q + 1, high);
		merge(arr, low, q, high);
	}
	return 0;
}

int merge(int* arr, int low, int q, int high){
    int left_size = q - low + 1;
    int right_size = high - q;
	int *right_arr, *left_arr, i = 0, j = 0, k;
	left_arr = (int*) malloc(sizeof(int)*left_size);	
	right_arr = (int*) malloc(sizeof(int)*right_size);

	memcpy(left_arr, arr+low, sizeof(int)*left_size);
	memcpy(right_arr, arr+low+left_size, sizeof(int)*right_size);
	
	for(k = low;k <= high;k++){
		if (j == right_size || (i < left_size && left_arr[i] <= right_arr[j])){
			arr[k] = left_arr[i];
			i++;
		} else {
			arr[k] = right_arr[j];
			j++;
		}
	}

	free(right_arr);
	free(left_arr);
	return 0;
}


