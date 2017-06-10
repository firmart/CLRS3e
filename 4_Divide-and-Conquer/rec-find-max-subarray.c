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
	//printf("Left : [%d, %d]\n", leftLow + 1, leftHigh + 1);
	leftSum = recFindMaxSubarray(arr, &leftLow, &leftHigh);
	//printf("Right : [%d, %d]\n", rightLow + 1, rightHigh + 1);
	rightSum = recFindMaxSubarray(arr, &rightLow, &rightHigh);
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

/*

int main(int argc, char** argv){
	int arr[16] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7}; //CLRS's example
	int Left = 0, Right = 15, sum;
	sum = findMaxSubarray(arr, &Left, &Right);
	printf("%d [%d, %d]\n", sum, Left + 1, Right + 1);
	return 0;
}
*/
