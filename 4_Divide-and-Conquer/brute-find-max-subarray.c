#include <stdio.h>
#include <limits.h>

#include "max_subarray.h"

int bruteFindMaxSubarray(int* arr, int* low, int* high){
	int n = *high - *low + 1;
	int period = -1;
	*low = *high = -1;
	int sum = INT_MIN;
	for(int i = 0; i < n; i++){	
		int tmpSum = 0;
		for (int tmpPeriod = 1; tmpPeriod < n - i + 1; tmpPeriod++){
			tmpSum = tmpSum + arr[i + tmpPeriod - 1];
			//printf("(i,p)=(%2d, %2d), tmpSum = %3d, sum = %3d\n", i + 1, tmpPeriod, tmpSum, sum);
			if (tmpSum > sum){
				*low = i;
				period = tmpPeriod;
				sum = tmpSum;
			}
		}
	}
	*high = *low + period - 1;
	return sum;
}


/*
int main(int argc, char** argv){
	int arr[16] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7}; //CLRS's example
	int sum, low = 0, high = 15;
	sum = bruteFindMaxSubarray(arr, &low, &high);
	printf("maxsubarray = [%d, %d], sum = %d\n", low + 1, high + 1, sum);  
	return 0;
}
*/
