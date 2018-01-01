#ifndef MAX_SUBARRAY_H
#define MAX_SUBARRAY_H

int bruteFindMaxSubarray(int* arr, int* low, int* high);
int recFindMaxSubarray(int* arr, int* low, int* high);
int hybridFindMaxSubarray(int* arr, int* low, int* high);
int findMaxCrossingSubarray(int* arr, int low, int mid, int high, int* crossLow, int* crossHigh); 
int linearFindMaxSubarray(int* arr, int* low, int* high);

#endif
