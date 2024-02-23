#include "functions.h"

double root_of_power(double x, int exponent, double eps)
{
    if(exponent > INT_MAX / 2 ){
        return INFINITY;
    }
    double value_current = 1;
    double value_next = (1.0/exponent)*((exponent - 1) * value_current + x/ binary_power(value_current, exponent-1));
    while(fabs(value_current - value_next) > eps){
        value_current = value_next;
        value_next = (1.0/exponent)*((exponent - 1) * value_current + x/ binary_power(value_current, exponent-1));
    }
    return value_next;
}

double old_approximate_power(double base, double exponent)
{
    union {
        double d;
        long long i;
    } u = {base};
    u.i = (long long)(4606853616395542500L + exponent * (u.i - 4606853616395542500L));
    return u.d;
}

double binary_power_recursive (double base, unsigned long long exponent)
{
    if (exponent == 0)
        return 1;
    if (exponent % 2 == 1)
        return binary_power_recursive(base, exponent-1) * base;
    else {
        double b = binary_power_recursive(base, exponent/2);
        return b * b;
    }
}

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

void binary(double base, unsigned long long exponent, double** results)
{
    (*results)[0] = binary_power_recursive(base, exponent);
    (*results)[1] = binary_power(base, exponent);
    (*results)[2] = pow(base, exponent);
}

int avg_geometric(double epsilon, double** results, int count, ...)
{
    va_list arguments;
    va_start(arguments, count);
    double result = 1.0;
    for(int i = 0; i < count; i++)
    {
        double xd = va_arg(arguments, double);
        result *= xd;
    }

    double exponent = 1.0/count;
    (*results)[0] = root_of_power(result, count, epsilon);
    (*results)[1] = old_approximate_power(result, exponent);
    (*results)[2] = pow(result, exponent);

    va_end(arguments);

    return SUCCESS;

}