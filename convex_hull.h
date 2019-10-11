//
// Created by vadim on 11.10.2019.
//

#ifndef PARK_SEM1_C_DZ1_CONVEX_HULL_H
#define PARK_SEM1_C_DZ1_CONVEX_HULL_H

#include <stdio.h>
#include "Stack.h"
#include "Point.h"

//Function to compute convex hull of a set of points
//Based on Graham-Scan convex hull algorithm.
void graham_scan(Point *points, size_t count, Stack *hull);

// check that boundary of hull is strictly convex
bool isConvex(Stack *hull);

#endif //PARK_SEM1_C_DZ1_CONVEX_HULL_H
