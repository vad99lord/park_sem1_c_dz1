#include <gtest/gtest.h>

//extern "C" {
#include "MergeSort.h"
#include "random_utils.h"
#include "Point.h"
//}

//sample compare function for ints
int compare_ints(const void *p, const void *q) {
    return *(const int *) p - *(const int *) q;
}

//comparator func to sort points by-coord
static int compare_by_y(const void *p, const void *q) {
    return *((Point *) p)->y - *((Point *) q)->y;
}

//run numOfSizes*numOfIters checks for mergesort
TEST(MergeTests, SortValidity) {
    //size array list
    //testing from 10 to 100000
    int numOfSizes = 5;
    int size[numOfSizes];
    srand(time(nullptr));
    size[0] = 10;
    for (int i = 1; i < numOfSizes; i++) {
        size[i] = size[i - 1] * 10;
    }
    int numOfIters = 5;

    int maxRand = 1000;
    for (int i = 0; i < numOfSizes; i++) {
        int *a = new int[size[i]];
        for (int j = 0; j < numOfIters; j++) {
            for (int k = 0; k < size[i]; k++) {
                a[k] = random_at_most(maxRand);
            }
            merge_sort(a, 0, size[i], size[i], sizeof(int), compare_ints);
            ASSERT_TRUE(isSorted(a, 0, size[i] - 1, sizeof(int), compare_ints));

        }
        delete[] a;
    }
}

TEST(MergeTests, SortPointValidity) {
    //size array list
    //testing from 10 to 10000
    int numOfSizes = 4;
    int size[numOfSizes];
    srand(time(nullptr));
    size[0] = 10;
    for (int i = 1; i < numOfSizes; i++) {
        size[i] = size[i - 1] * 10;
    }
    int numOfIters = 5;

    int maxRand = 1000;

    for (int i = 0; i < numOfSizes; i++) {
        int *x = new int[size[i]];
        int *y = new int[size[i]];
        Point *points = new Point[size[i]];
        for (int j = 0; j < numOfIters; j++) {
            //init random coords
            for (int k = 0; k < size[i]; k++) {
                x[k] = random_at_most_signed(maxRand);
                y[k] = random_at_most_signed(maxRand);
                points[k].pos = k;
                points[k].x = &x[k];
                points[k].y = &y[k];
            }

            merge_sort(points, 0, size[i], size[i], sizeof(Point), compare_by_y);
            ASSERT_TRUE(isSorted(points, 0, size[i] - 1, sizeof(Point), compare_by_y));

        }
        delete[] points;
        delete[] x;
        delete[] y;
    }
}
