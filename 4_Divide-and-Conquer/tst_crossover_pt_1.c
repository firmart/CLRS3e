#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "max_subarray.h"

#define ARR_DFLT_SZ 511
#define TOTAL_TST 10000

#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

int main(int argc, char** argv){
	srand(time(NULL));
	int* arr, n = 1, tst = 0;
	int low = 0, high = 0;
	double avg = 0;
	struct timespec start, end;
	double time_bf, time_rec;
	
	arr = (int*)malloc(sizeof(int)*ARR_DFLT_SZ);
	
	/* Create an instance of max-subarray problem  */
	
	for (int i = 0; i < ARR_DFLT_SZ; i++){
		arr[i] = rand() % 201 - 100;
	} 	

	/* Execute test  */

    while(tst < TOTAL_TST) {

		/* Brute-force algorithm */

		low = 0; high = n;
		clock_gettime(CLOCK_MONOTONIC, &start);
		bruteFindMaxSubarray(arr, &low, &high);
		clock_gettime(CLOCK_MONOTONIC, &end);
	
		time_bf = (double)(end.tv_sec - start.tv_sec) * 1.0e9 + (double)(end.tv_nsec - start.tv_nsec);

		/* Recursive algorithm */

		low = 0; high = n;	
		clock_gettime(CLOCK_MONOTONIC, &start);
		recFindMaxSubarray(arr, &low, &high);
		clock_gettime(CLOCK_MONOTONIC, &end);

		time_rec = (double)(end.tv_sec - start.tv_sec) * 1.0e9 + (double)(end.tv_nsec - start.tv_nsec);
        
        if (time_bf > time_rec) {
			tst++;
			avg += n + 1;
			n = 1;
			continue;
        }
        n++;
    }

	printf("Average Crossover point : " YEL "%lf\n" RESET, avg/TOTAL_TST);
	free(arr);
	return 0;
}
