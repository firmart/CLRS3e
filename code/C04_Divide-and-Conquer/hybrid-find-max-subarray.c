#include <stdio.h>

#include "max_subarray.h"

int hybridFindMaxSubarray(int* arr, int* low, int* high){
	if (*high - *low + 1 <= 17) // base case
		return arr[*low]; 
	int mid = (*low + *high)/2; // division
	int leftLow = *low, leftHigh = mid, leftSum;
	int rightLow = mid + 1, rightHigh = *high, rightSum;
	int crossLow, crossHigh, crossSum;
	//printf("Left : [%d, %d]\n", leftLow + 1, leftHigh + 1);
	leftSum = hybridFindMaxSubarray(arr, &leftLow, &leftHigh);
	//printf("Right : [%d, %d]\n", rightLow + 1, rightHigh + 1);
	rightSum = hybridFindMaxSubarray(arr, &rightLow, &rightHigh);
	//printf("Cross : [%d, %d]\n", *low, *high);
	crossSum = findMaxCrossingSubarray(arr, *low, mid, *high, &crossLow, &crossHigh);
	if (leftSum >= rightSum && leftSum >= crossSum){
		*low = 	leftLow;
		*high = leftHigh;
		return leftSum;
	} else if (rightSum >= leftSum && rightSum >= crossSum){
		*low = rightLow;
		*high = rightHigh;
		return rightSum;
	} else {
		*low = crossLow;
		*high = crossHigh;
		return crossSum;
	}
}
