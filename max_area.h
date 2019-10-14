//
// Created by vadim on 11.10.2019.
//

#ifndef PARK_SEM1_C_DZ1_MAX_AREA_H
#define PARK_SEM1_C_DZ1_MAX_AREA_H

#include <stdio.h>
#include "Point.h"


static const size_t vertex = 3;

double calc_triangle_area(Point a, Point b, Point c);

//calculate max triangle area based on two arrays of pointers to ints
void max_area(int **xCoords, int **yCoords, size_t size, int **pointsPos, int *vertices);

void points_from_array(int **xCoords, int **yCoords, size_t size, Point *point);

void find_max_area_hull(Point *points, size_t size, int *vertices);

#endif //PARK_SEM1_C_DZ1_MAX_AREA_H
