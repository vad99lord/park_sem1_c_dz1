#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "MergeSort.h"

bool isSorted(const void *a, size_t lo, size_t hi, size_t size,
              int (*comp)(const void *, const void *)) {
    for (size_t i = lo + 1; i <= hi; i++)
        if (comp(&((const char *) a)[i * size], &((const char *) a)[(i - 1) * size]) < 0)
            return false;
    return true;
}


//merge a[lo .. mid] with a[mid+1 ..hi]
static void merge(void *a, void *aux, size_t lo, size_t mid, size_t hi, size_t size,
                  int (*comp)(const void *, const void *)) {
    // precondition: a[lo .. mid] and a[mid+1 .. hi] are sorted subarrays
    assert (isSorted(a, lo, mid, size, comp));
    assert (isSorted(a, mid + 1, hi, size, comp));

    // copy to aux[]
    /* for (size_t k = lo; k <= hi; k++) {
        aux[k] = a[k];
    } */
    memcpy(&((char *) aux)[lo * size], &((const char *) a)[lo * size], (hi - lo + 1) * size);


    // merge back to a[]
    size_t i = lo, j = mid + 1;
    for (size_t k = lo; k <= hi; k++) {
        if (i > mid) {
            //a[k] = aux[j++];
            memcpy(&((char *) a)[k * size], &((const char *) aux)[j * size], size);
            j++;
        } else if (j > hi) {
            //a[k] = aux[i++];
            memcpy(&((char *) a)[k * size], &((const char *) aux)[i * size], size);
            i++;
        } else if (comp(&((const char *) aux)[j * size], &((const char *) aux)[i * size]) < 0) {
            //a[k] = aux[j++];
            memcpy(&((char *) a)[k * size], &((const char *) aux)[j * size], size);
            j++;
        } else {
            //a[k] = aux[i++];
            memcpy(&((char *) a)[k * size], &((const char *) aux)[i * size], size);
            i++;
        }
    }

    //postcondition: a[lo .. hi] is sorted
    assert (isSorted(a, lo, hi, size, comp));
}


// mergesort a[lo..hi]
static void sort(void *a, void *aux, size_t lo, size_t hi, size_t size,
                 int (*comp)(const void *, const void *)) {
    if (hi <= lo) return;
    size_t mid = lo + (hi - lo) / 2;
    sort(a, aux, lo, mid, size, comp);
    sort(a, aux, mid + 1, hi, size, comp);
    merge(a, aux, lo, mid, hi, size, comp);
}


void merge_sort(void *a, size_t lo, size_t hi, size_t count, size_t size, int (*comp)(const void *, const void *)) {
    assert (lo < hi);
    assert (hi <= count);
    void *aux = malloc(hi * size);
    sort(a, aux, lo, hi - 1, size, comp);
    free(aux);
}




