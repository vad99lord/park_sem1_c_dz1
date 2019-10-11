#include "main.h"
#include "convex_hull.h"
#include <assert.h>
#include "MergeSort.h"

//pivot point(with lowest y-coordinate for convex hull algorithm)
static Point pivot;


//comparator func to sort points by-coord
static int compare_by_y(const void *p, const void *q) {
    return *((Point *) p)->y - *((Point *) q)->y;
}

//comparator func to sort points by-coord
static int compare_by_x(const void *p, const void *q) {
    return *((Point *) p)->x - *((Point *) q)->x;
}

//function to check counterclockwise turn.
//clockwise=-1, collinear=0; counterclockwise=1.
static int ccw(Point a, Point b, Point c) {
    double area2 = (*b.x - *a.x) * (*c.y - *a.y) - (*b.y - *a.y) * (*c.x - *a.x);
    if (area2 < 0) {
        return -1;
    }
    if (area2 > 0) {
        return +1;
    }
    return 0;
}

//comparator func to sort points by-polar
//according to the pivot point
static int compare_by_polar(const void *q1, const void *q2) {
    double dx1 = *((Point *) q1)->x - *pivot.x;
    double dy1 = *((Point *) q1)->y - *pivot.y;
    double dx2 = *((Point *) q2)->x - *pivot.x;
    double dy2 = *((Point *) q2)->y - *pivot.y;

    if (dy1 >= 0 && dy2 < 0) {
        // q1 above; q2 below
        return -1;
    }
    if (dy2 >= 0 && dy1 < 0) {
        // q1 below; q2 above
        return +1;
    }
    if (dy1 == 0 && dy2 == 0) {
        // 3-collinear and horizontal
        if (dx1 >= 0 && dx2 < 0)
            return -1;
        if (dx2 >= 0 && dx1 < 0)
            return +1;
        return 0;
    }
    // both above or below
    return -ccw(pivot, *(Point *) q1, *(Point *) q2);
}

// check that boundary of hull is strictly convex
bool isConvex(Stack *hull) {
    size_t n = stack_size(hull);
    if (n <= 2) return true;
    Point *points = malloc(n * sizeof(Point));
    //stack to array
    iterator_fifo(hull, points);

    for (int i = 0; i < n; i++) {
        if (ccw(points[i], points[(i + 1) % n], points[(i + 2) % n]) < 0) {
            return false;
        }
    }
    free(points);
    return true;
}

//Function to compute convex hull of a set of points
//Based on Graham-Scan convex hull algorithm.
void graham_scan(Point *points, size_t count, Stack *hull) {

    //sort by x-coord firstly
    merge_sort(points, 0, count, count, sizeof(Point), compare_by_x);

    //sort by y-coord
    merge_sort(points, 0, count, count, sizeof(Point), compare_by_y);

    pivot = points[0];

    //sort by polar angle with respect to pivot point a[0]
    merge_sort(points, 1, count, count, sizeof(Point), compare_by_polar);

    // a[0] is first extreme point
    push(hull, &pivot);

    // find k1 != a[0]
    size_t k1;
    for (k1 = 1; k1 < count; k1++)
        if (*points[k1].x != *pivot.x || *points[k1].y != *pivot.y)
            break;
    if (k1 == count) return;

    // find index k2 not collinear with a[0] and a[k1]
    size_t k2;
    for (k2 = k1 + 1; k2 < count; k2++)
        if (ccw(pivot, points[k1], points[k2]) != 0)
            break;
    if (k2 == count) return;
    push(hull, &points[k2 - 1]);


    // Graham scan;
    Point *top = malloc(sizeof(Point));
    for (size_t i = k2; i < count; i++) {
        pop(hull, top);
        while (ccw(*(Point *) peek(hull), *top, points[i]) <= 0) {
            pop(hull, top);
        }
        push(hull, top);
        push(hull, &points[i]);

    }
    free(top);

    assert (isConvex(hull));
}


