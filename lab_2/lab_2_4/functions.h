
#ifndef LAB_2_4_FUNCTIONS_H
#define LAB_2_4_FUNCTIONS_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

enum exit_codes
{
    memory_error,
    convex,
    concave,
};

typedef struct point_2d
{
    double x;
    double y;
} point_2d;

typedef struct polygon
{
    point_2d* points;
} polygon;

double binary_power(double base, unsigned long long exponent);
int is_convex(int vertex_amount, ...);
double polynomial(double value, int degree, ...);

#endif //LAB_2_4_FUNCTIONS_H
