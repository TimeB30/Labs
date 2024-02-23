#include "functions.h"
#define EQUATION ((value*7 - M_PI*4/3)/ sin(value))

double equation(double a, double b, double epsilon, double eq_(double))
{
    double middle;
    while(fabs(a-b)>epsilon)
    {
        middle = (a+b)/2;
        if(eq_(a)  * eq_(middle) > 0) a = middle;
        else if (eq_(b) * eq_(middle) > 0) b = middle;
        else return middle;
    }
    return middle;
}

double eq_(double value)
{
    return EQUATION;
}