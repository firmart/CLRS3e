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


