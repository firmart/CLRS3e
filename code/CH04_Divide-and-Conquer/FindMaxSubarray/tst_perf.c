#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "max_subarray.h"

#define ARR_DFLT_SZ 500

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

int main(int argc, char** argv){
	srand(time(NULL));
	int* arr;
	int low = 0, high = 0, sum;
	long n;
	struct timespec start, end;
	double time_bf, time_rec, time_hyb;

	if (argc > 1)
		n = atol(argv[1]);
	n = n > 0 ? n : ARR_DFLT_SZ;
	
	arr = (int*)malloc(sizeof(int) * n);
	
	/* Create an instance of max-subarray problem  */
	
	for (int i = 0; i < n; i++){
		arr[i] = rand() % 201 - 100;
	} 	

		/* Brute-force algorithm */

	low = 0; high = n - 1;
	clock_gettime(CLOCK_MONOTONIC, &start);
	sum = bruteFindMaxSubarray(arr, &low, &high);
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	time_bf = (double)(end.tv_sec - start.tv_sec) * 1.0e9 + (double)(end.tv_nsec - start.tv_nsec);


	/* Recursive algorithm */

	low = 0; high = n - 1;	
	clock_gettime(CLOCK_MONOTONIC, &start);
	sum = recFindMaxSubarray(arr, &low, &high);
	clock_gettime(CLOCK_MONOTONIC, &end);

	time_rec = (double)(end.tv_sec - start.tv_sec) * 1.0e9 + (double)(end.tv_nsec - start.tv_nsec);
        

	/* Hybrid algorithm */

	low = 0; high = n - 1;	
	clock_gettime(CLOCK_MONOTONIC, &start);
	sum = hybridFindMaxSubarray(arr, &low, &high);
	clock_gettime(CLOCK_MONOTONIC, &end);

	time_hyb = (double)(end.tv_sec - start.tv_sec) * 1.0e9 + (double)(end.tv_nsec - start.tv_nsec);
       
	if (time_hyb < time_rec && time_rec < time_bf){
		printf("Hybrid Algorithm :      " GRN  "%10.0lfns" RESET ", max-subarray=[%d, %d], sum = %d\n", time_hyb, low + 1, high + 1, sum);
		printf("Recursive Algorithm :   " YEL  "%10.0lfns" RESET ", max-subarray=[%d, %d], sum = %d\n", time_rec, low + 1, high + 1, sum);
		printf("Brute-force Algorithm : " RED  "%10.0lfns" RESET ", max-subarray=[%d, %d], sum = %d\n", time_bf, low + 1, high + 1, sum);
	} else if (time_hyb < time_bf && time_bf < time_rec) {
		printf("Hybrid Algorithm :      " GRN  "%10.0lfns" RESET ", max-subarray=[%d, %d], sum = %d\n", time_hyb, low + 1, high + 1, sum);
		printf("Brute-force Algorithm : " YEL  "%10.0lfns" RESET ", max-subarray=[%d, %d], sum = %d\n", time_bf, low + 1, high + 1, sum);
		printf("Recursive Algorithm :   " RED  "%10.0lfns" RESET ", max-subarray=[%d, %d], sum = %d\n", time_rec, low + 1, high + 1, sum);
	} else {
		printf("Hybrid Algorithm :      %10.0lfns, max-subarray=[%d, %d], sum = %d\n", time_hyb, low + 1, high + 1, sum);
		printf("Brute-force Algorithm : %10.0lfns, max-subarray=[%d, %d], sum = %d\n", time_bf, low + 1, high + 1, sum);
		printf("Recursive Algorithm :   %10.0lfns, max-subarray=[%d, %d], sum = %d\n", time_rec, low + 1, high + 1, sum);
	}
 
	free(arr);
	return 0;
}
