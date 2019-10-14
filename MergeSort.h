//
// Created by vadim on 09.10.2019.
//

#ifndef PARK_SEM1_C_DZ1_MERGESORT_H
#define PARK_SEM1_C_DZ1_MERGESORT_H

#include <stdbool.h>

/**
 *merge_sort function generic implementation
 *@a = array to sort
 *@lo = left bound of sort inclusively
 *@hi = right bound of sort exclusively
 *@count = num of elems
 *@size = size of 1 elem
 *@comp = comparator function
*/
void merge_sort(void *a, size_t lo, size_t hi, size_t count, size_t size,
                int (*comp)(const void *, const void *));

//helper method to test if array is sorted
bool isSorted(const void *a, size_t lo, size_t hi, size_t size,
              int (*comp)(const void *, const void *));


#endif //PARK_SEM1_C_DZ1_MERGESORT_H
