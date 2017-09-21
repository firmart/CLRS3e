#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "max_subarray.h"

#define ARR_DFLT_SZ 500

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

void print_arr(int* arr,int size){
	for(int i = 0; i < size; i++)
		printf("%d ",arr[i]);
	puts("");
}

int main(int argc, char** argv){
	srand(time(NULL));
	
	long n;
	if (argc > 1)
		n = atol(argv[1]);
	n = n > 0 ? n : ARR_DFLT_SZ;
	
	int* arr;
	int low_bf = 0, high_bf = n - 1, sum_bf;
	int low_rec = 0, high_rec = n - 1, sum_rec;
	int low_hyb = 0, high_hyb = n - 1, sum_hyb;
	int low_lin = 0, high_lin = n - 1, sum_lin;
	struct timespec start, end;
	double time_bf, time_rec, time_hyb, time_lin;

	
	arr = (int*)malloc(sizeof(int) * n);
	
	/* Create an instance of max-subarray problem  */
	
	for (int i = 0; i < n; i++){
		arr[i] = rand() % 201 - 100;
	} 	
	
	print_arr(arr, n);

	/* Brute-force algorithm */

	clock_gettime(CLOCK_MONOTONIC, &start);
	sum_bf = bruteFindMaxSubarray(arr, &low_bf, &high_bf);
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	time_bf = (double)(end.tv_sec - start.tv_sec) * 1.0e9 + (double)(end.tv_nsec - start.tv_nsec);


	/* Recursive algorithm */

	clock_gettime(CLOCK_MONOTONIC, &start);
	sum_rec = recFindMaxSubarray(arr, &low_rec, &high_rec);
	clock_gettime(CLOCK_MONOTONIC, &end);

	time_rec = (double)(end.tv_sec - start.tv_sec) * 1.0e9 + (double)(end.tv_nsec - start.tv_nsec);
        

	/* Hybrid algorithm */

	clock_gettime(CLOCK_MONOTONIC, &start);
	sum_hyb = hybridFindMaxSubarray(arr, &low_hyb, &high_hyb);
	clock_gettime(CLOCK_MONOTONIC, &end);

	time_hyb = (double)(end.tv_sec - start.tv_sec) * 1.0e9 + (double)(end.tv_nsec - start.tv_nsec);
	
	/* Linear algorithm */

	clock_gettime(CLOCK_MONOTONIC, &start);
	sum_lin = linearFindMaxSubarray(arr, &low_lin, &high_lin);
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	time_lin = (double)(end.tv_sec - start.tv_sec) * 1.0e9 + (double)(end.tv_nsec - start.tv_nsec);

		printf("Linear Algorithm :      " GRN  "%10.0lfns" RESET ", max-subarray=[%d, %d], sum = %d\n", time_lin, low_lin + 1, high_lin + 1, sum_lin);
		printf("Hybrid Algorithm :      " GRN  "%10.0lfns" RESET ", max-subarray=[%d, %d], sum = %d\n", time_hyb, low_hyb + 1, high_hyb + 1, sum_hyb);
		printf("Recursive Algorithm :   " YEL  "%10.0lfns" RESET ", max-subarray=[%d, %d], sum = %d\n", time_rec, low_rec + 1, high_rec + 1, sum_rec);
		printf("Brute-force Algorithm : " RED  "%10.0lfns" RESET ", max-subarray=[%d, %d], sum = %d\n", time_bf, low_bf + 1, high_bf + 1, sum_bf);
 
	free(arr);
	return 0;
}
