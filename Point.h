#ifndef PARK_SEM1_C_DZ1_POINT_H
#define PARK_SEM1_C_DZ1_POINT_H

//immutable points struct since we won't change values of provided points
struct Point {
    const int *x;
    const int *y;
    int pos; //position of point in initial array;
};

typedef struct Point Point;

#endif //PARK_SEM1_C_DZ1_POINT_H
