#include <stdio.h>

#include "max_subarray.h"

//should use the value got from tst_crossover_pt_1
#define CROSSOVER 11

int hybridFindMaxSubarray(int* arr, int* low, int* high){
	int deref_high = *high, deref_low = *low;
	if (*high - *low + 1 <= CROSSOVER) // base case
		return bruteFindMaxSubarray(arr, &deref_low, &deref_high);//TODO: Bug, rewrite with structure
	int mid = (*low + *high)/2; // division
	int leftLow = *low, leftHigh = mid, leftSum;
	int rightLow = mid + 1, rightHigh = *high, rightSum;
	int crossLow, crossHigh, crossSum;
	leftSum = hybridFindMaxSubarray(arr, &leftLow, &leftHigh);
	//printf("Left : [%d, %d], leftSum = %d\n", leftLow + 1, leftHigh + 1, leftSum);
	rightSum = hybridFindMaxSubarray(arr, &rightLow, &rightHigh);
	//printf("Right : [%d, %d], rightSum = %d\n", rightLow + 1, rightHigh + 1, rightSum);
	crossSum = findMaxCrossingSubarray(arr, *low, mid, *high, &crossLow, &crossHigh);
	//printf("Cross : [%d, %d], crossSum = %d\n", crossLow + 1, crossHigh + 1, crossSum);
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

