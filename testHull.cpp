#include <gtest/gtest.h>
//extern "C" {
#include "convex_hull.h"
#include "random_utils.h"
#include "Point.h"
//}

TEST(HullTests, ConvexValidity) {
    //size array list
    //testing from 10 to 1000000
    int numOfSizes = 5;
    int size[numOfSizes];
    srand(time(nullptr) );
    size[0]=10;
    for (int i =1;i<numOfSizes;i++){
        size[i]=size[i-1]*10;
    }
    int numOfIters = 5;

    int maxRand = 1000;

    for (int i = 0;i<numOfSizes;i++){
        int* x = new int[size[i]];
        int* y = new int[size[i]];
        Point* points = new Point[size[i]];
        for (int j = 0;j<numOfIters;j++){
            Stack* hull = create_stack(sizeof(Point));
            //init random coords
            for(int k = 0; k < size[i]; k++) {
                x[k] = random_at_most_signed(maxRand);
                y[k] = random_at_most_signed(maxRand);
                points[k].pos = k;
                points[k].x = &x[k];
                points[k].y = &y[k];
            }
            graham_scan(points,size[i],hull);
            ASSERT_TRUE(isConvex(hull))<< "size = "<<size[i]<<"iter ="<<j;
            delete_stack(hull);
        }
        delete[] points;
        delete[] x;
        delete[] y;
    }
}
