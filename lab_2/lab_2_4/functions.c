
#include "functions.h"

double binary_power(double base, unsigned long long exponent)
{
    double v = 1.0;
    while(exponent){
        if(exponent & 1){
            v *= base;
        }
        base *= base;
        exponent >>= 1;
    }
    return v;
}


int is_convex(int vertex_amount, ...)
{
    va_list args;
    va_start(args, vertex_amount);

    point_2d* polygon = (point_2d*)malloc(sizeof(point_2d)*vertex_amount);
    if(polygon == NULL)
    {
        return memory_error;
    }

    for(int i = 0; i < vertex_amount; i++)
    {
        polygon[i] = va_arg(args, point_2d);
    }
    va_end(args);

    int i,j,k;
    int flag = 0;
    double z;

    if (vertex_amount < 3)
        return(0);

    for (i = 0; i < vertex_amount; i++)
    {
        j = (i + 1) % vertex_amount;
        k = (i + 2) % vertex_amount;

        z  = (polygon[j].x - polygon[i].x) * (polygon[k].y - polygon[j].y);
        z -= (polygon[j].y - polygon[i].y) * (polygon[k].x - polygon[j].x);
        if (z < 0)
            flag |= 1;
        else if (z > 0)
            flag |= 2;
        if (flag == 3)
            return(convex);
    }
    if (flag != 0)
        return(concave);
    else
        return(convex);
}

double polynomial(double value, int degree, ...)
{
    va_list args;
    va_start(args, degree);
    double result = 0;

    for(int exponent = degree; exponent >= 0; exponent--)
    {
        double coefficient = va_arg(args, double);
        result += coefficient * binary_power(value, exponent);
    }
    va_end(args);
    return result;
}