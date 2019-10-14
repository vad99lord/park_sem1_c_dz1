#include <gtest/gtest.h>
#include "max_area.h"
#include "random_utils.h"
#include "Point.h"
#include "MergeSort.h"

//sample compare function for ints
int compare_by_ints(const void *p, const void *q)
{
    return *(const int*)p-*(const int*)q;
}

int* find_max_area_brute(int ** xCoords, int** yCoords, size_t size, int* vertices){
    Point* points = new Point[size];
    for (size_t i = 0;i<size;i++){
        points[i].x = xCoords[i];
        points[i].y = yCoords[i];
        points[i].pos = i;
    }
    //points that give max possible area
    size_t ma=0,mb=1,mc=2;

    double maxArea = 0.0;
    double area = maxArea;
    for (size_t i = 0;i<size-2; i++){
        for (size_t j = 1;j<size-1; j++){
            for (size_t k = 2;k<size; k++){
                area = calc_triangle_area(points[i],points[j],points[k]);
                if (area>maxArea){
                    maxArea = area;
                    ma=i;
                    mb=j;
                    mc=k;
                }
            }
        }
    }
    vertices[0]=points[ma].pos;
    vertices[1]=points[mb].pos;
    vertices[2]=points[mc].pos;
    delete[] points;
    return vertices;
}




bool isEqual(const int* a ,const int* b, int size){
    for (int i=0;i<size;i++){
        if (a[i]!=b[i])
            return false;
    }
    return true;
}



TEST(AreaTests, AreaValidity) {
    //size array list
    //testing from 10 to 1000000
    int numOfSizes = 3;
    int size[numOfSizes];
    srand(time(nullptr) );
    size[0]=10;
    for (int i =1;i<numOfSizes;i++){
        size[i]=size[i-1]*5;
    }
    int numOfIters = 4;

    int maxRand = 1000;

    int **pointsPos = (int**)malloc(3 * sizeof(int *));
    int *vertices = (int*)malloc(3 * sizeof(int));

    int *bruteVertices = new int[3];

    for (int i = 0;i<numOfSizes;i++){
        int* x = new int[size[i]];
        int* y = new int[size[i]];
        int** xPoints = new int*[size[i]];
        int** yPoints = new int*[size[i]];
        for (int j = 0;j<numOfIters;j++){
            //init random coords
            for(int k = 0; k < size[i]; k++) {
                x[k] = random_at_most_signed(maxRand);
                y[k] = random_at_most_signed(maxRand);
                xPoints[k] = &x[k];
                yPoints[k] = &y[k];
            }

            max_area(xPoints,yPoints,size[i],pointsPos,vertices);
            find_max_area_brute(xPoints,yPoints,size[i],bruteVertices);
            merge_sort(vertices,0,3,3,sizeof(int),compare_by_ints);
            merge_sort(bruteVertices,0,3,3,sizeof(int),compare_by_ints);
            ASSERT_TRUE(isEqual(vertices,bruteVertices,3));
        }

        delete[] x;
        delete[] y;
        delete[] xPoints;
        delete[] yPoints;
    }
    delete[] bruteVertices;
    free(vertices);
    free(pointsPos);
}
