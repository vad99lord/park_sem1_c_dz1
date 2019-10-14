#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "MergeSort.h"
#include "random_utils.h"


//sample compare function for ints
int compare_ints(const void *p, const void *q) {
    return *(const int *) p - *(const int *) q;
}

int main() {
    int n=10;
    int *a = malloc(10 * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        a[i] = random_at_most(1000);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
        printf("\n");
    }

    printf("\n");
    printf("\n");


    merge_sort(a, 0, n, n, sizeof(int), compare_ints);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
        printf("\n");
    }
    free(a);
    return 0;
}
