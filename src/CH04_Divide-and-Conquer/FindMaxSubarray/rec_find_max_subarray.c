#include <stdio.h>
#include <limits.h>

#include "max_subarray.h"

int findMaxCrossingSubarray(int* arr, int low, int mid, int high, int* maxLeft, int* maxRight){
	int leftSum = INT_MIN, rightSum = INT_MIN;
	int sum = 0;
	for(int i = mid; i >= low; i--){
		sum = sum + arr[i];
		if (sum > leftSum){
			leftSum = sum;
			*maxLeft = i;
		}
	}
	sum = 0;
	for(int j = mid + 1; j <= high; j++){
		sum = sum + arr[j];
		if (sum > rightSum){
			rightSum = sum;
			*maxRight = j;
		}
	}
	return leftSum + rightSum;
}

int recFindMaxSubarray(int* arr, int* low, int* high){
	if (*high == *low) // base case
		return arr[*low]; 
	int mid = (*low + *high)/2; // division
	int leftLow = *low, leftHigh = mid, leftSum;
	int rightLow = mid + 1, rightHigh = *high, rightSum;
	int crossLow, crossHigh, crossSum;
	leftSum = recFindMaxSubarray(arr, &leftLow, &leftHigh);
	//printf("Left : [%d, %d], leftSum = %d\n", leftLow + 1, leftHigh + 1, leftSum);
	rightSum = recFindMaxSubarray(arr, &rightLow, &rightHigh);
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

