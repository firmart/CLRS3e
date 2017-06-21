#include "max_subarray.h"

/* Kadane's algorithm  */

int linearFindMaxSubarray(int* arr, int* low, int* high){
	int sum = arr[0], tmp_sum = arr[0], tmp_left = 0, tmp_right = 0;
	int size = *high - *low;
	for (int i = *low + 1; i <= size; i++){
		if (tmp_sum < 0){
			tmp_sum = arr[i];
			tmp_left = tmp_right = i;
		} else {
			tmp_sum += arr[i];
			tmp_right++;
		}
		if (sum < tmp_sum){
			sum = tmp_sum;
			*high = tmp_right;
			*low = tmp_left;
		}
	}
	return sum;
}

