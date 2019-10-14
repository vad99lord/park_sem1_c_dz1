#include <time.h>
#include <stdlib.h>
#include "max_area.h"
#include "random_utils.h"


static void read_points(int **x, int **y, int *xCoords, int *yCoords, size_t count) {
    for (size_t i = 0; i < count; i++) {
        int a, b;
        scanf("%d", &a);
        scanf("%d", &b);
        xCoords[i] = a;
        x[i] = &xCoords[i];
        yCoords[i] = b;
        y[i] = &yCoords[i];
    }
}

static void read_rand(int **x, int **y, int *xCoords, int *yCoords, size_t count) {
    for (size_t i = 0; i < count; i++) {
        xCoords[i] = random_at_most(100);
        yCoords[i] = random_at_most(100);
    }
    for (size_t i = 0; i < count; i++) {
        x[i] = &xCoords[i];
        y[i] = &yCoords[i];
    }
}

int main() {
    //size of array
    int n = 0;
    srand(time(NULL));
    scanf("%d", &n);
    size_t count = n;

    //array of pointers to x and y coords
    int **xCoords = malloc(count * sizeof(int *));
    int **yCoords = malloc(count * sizeof(int *));

    //helper create of 1d array
    //then put each address of this 1d array to corresponding 2-d array
    int *xCoordsVals = malloc(count * sizeof(int));
    int *yCoordsVals = malloc(count * sizeof(int));

    read_points(xCoords, yCoords, xCoordsVals, yCoordsVals, count);
    //read_rand(xCoords,yCoords,xCoordsVals,yCoordsVals,count);


    /*
    //simple print loop
    printf("%d\n", n);
    for (size_t i = 0; i < n; i++) {
        printf("(%d ,", *xCoords[i]);
        printf("%d)\n", *yCoords[i]);
    }
    */


    int **pointsPos = malloc(vertex * sizeof(int *));
    int *vertices = malloc(vertex * sizeof(int));

    max_area(xCoords, yCoords, n, pointsPos, vertices);


    //simple print loop
    Point points[3];
    for (size_t i = 0; i < vertex; i++) {
        printf("точка номер: ");
        printf("%d", *pointsPos[i]);
        printf(", координаты : ");
        printf("(%d ,", *xCoords[*pointsPos[i]]);
        printf("%d)\n", *yCoords[*pointsPos[i]]);
        points[i].x = xCoords[*pointsPos[i]];
        points[i].y = yCoords[*pointsPos[i]];
    }
    printf("площадь треугольника:\n");
    printf("%f\n", calc_triangle_area(points[0], points[1], points[2]));


    //free memory of coords and coordsVals arrays;
    free(yCoordsVals);
    free(xCoordsVals);
    free(xCoords);
    free(yCoords);
    free(vertices);
    free(pointsPos);
    return 0;
}