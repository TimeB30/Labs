#include "functions.h"

double old_approximate_power(double base, double exponent)
{
    union
    {
        double d;
        long long i;
    }
    u = {base};
    u.i = (long long)(4606853616395542500L + exponent * (u.i - 4606853616395542500L));
    return u.d;
}

int check_double(char** word)
{
    double value;
    char* end;
    value = strtod(*word, &end);

    if(*end != 0)
    {
        return not_a_number;
    }
    if(value <= 0.0)
    {
        return negative_or_zero;
    }
    return positive;
}

double task_a(double x)
{
    return log(1+x)/x;
}

double task_b(double x)
{
    return exp(-(x*x)/2);
}

double task_c(double x)
{
    double result = -log(1-x);
    return result;
}

double task_d(double x)
{
    return old_approximate_power(x, x);
}

double trapezoid(double function(double), double a, double b,double epsilon)
{
    if(floor(epsilon) > 0.0) return 1;
    int n = ceil((b-a)/epsilon);
    double result = epsilon * (function(a+epsilon) + function(b-epsilon)) / 2;
    for(int i = 1; i < n; i++)
    {
        result += epsilon * function(a + epsilon*i);
    }
    return result;
}