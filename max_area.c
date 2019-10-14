#include <math.h>
#include <assert.h>
#include "max_area.h"
#include "Point.h"
#include "convex_hull.h"
#include "Stack.h"

double calc_triangle_area(Point a, Point b, Point c) {
    double area = (*a.x - *c.x) * (*b.y - *a.y) - (*a.x - *b.x) * (*c.y - *a.y);
    return fabs(area * 0.5);
}

static void find_max_points(Point *points, size_t count, int *vertices) {
    //initial points position for search
    size_t a = 0, b = 1, c = 2;
    //points that give max possible area
    size_t ma = a, mb = b, mc = c;
    //iterate a
    while (true) {
        //iterate b
        while (true) {
            //iterate c
            while (calc_triangle_area(points[a], points[b], points[c])
                   <= calc_triangle_area(points[a], points[b], points[(c + 1) % count])) {
                c = (c + 1) % count;
            }
            //check if b advance helps
            if (calc_triangle_area(points[a], points[b], points[c])
                <= calc_triangle_area(points[a], points[(b + 1) % count], points[c])) {
                b = (b + 1) % count;
                continue;
            } else
                break;
        }
        if (calc_triangle_area(points[a], points[b], points[c])
            > calc_triangle_area(points[ma], points[mb], points[mc])) {
            ma = a;
            mb = b;
            mc = c;
        }
        a = (a + 1) % count;
        if (a == b) {
            b = (b + 1) % count;
        }
        if (b == c) {
            c = (c + 1) % count;
        }
        if (a == 0) {
            break;
        }
    }
    vertices[0] = points[ma].pos;
    vertices[1] = points[mb].pos;
    vertices[2] = points[mc].pos;
}

void find_max_area_hull(Point *points, size_t size, int *vertices) {
    Stack *hull = create_stack(sizeof(Point));
    graham_scan(points, size, hull);
    Point *hullPoints = malloc(stack_size(hull) * sizeof(Point));
    iterator_fifo(hull, hullPoints);
    size_t count = stack_size(hull);
    find_max_points(hullPoints, count, vertices);
    delete_stack(hull);
    free(hullPoints);
}


void points_from_array(int **xCoords, int **yCoords, size_t size, Point *points) {
    for (size_t i = 0; i < size; i++) {
        points[i].x = xCoords[i];
        points[i].y = yCoords[i];
        points[i].pos = i;
    }
}

void max_area(int **xCoords, int **yCoords, size_t size, int **pointsPos, int *vertices) {
    assert(size >= 3);
    //make pointer array from two input arrays;
    Point *points = malloc(size * sizeof(Point));
    points_from_array(xCoords, yCoords, size, points);
    find_max_area_hull(points, size, vertices);
    for (int i = 0; i < vertex; i++) {
        pointsPos[i] = &vertices[i];
    }
    free(points);
}
