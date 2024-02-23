#include "functions.h"

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

double row_a(int n , double x, double current)
{
    if (n == 0) return 1;
    return current*x/n;
}
double row_b(int n, double x, double current)
{
    if(n == 0) return 1;
    return current * (-1) * x * x / ((2*n-1) * (2*n));
}
double row_c(int n, double x, double current)
{
    if(n == 0) return 1;
    for(int i = 3*(n-1)+1; i < 3*n; i++)
    {
        current /= i;
    }
    current = current * 3 * 3 *  n * n * x * x;
    return current;
}
double row_d(int n, double x, double current)
{
    n++;
    if(n == 1) return -(x * x)/2;
    current *= (2*n-1);
    current /= 2*n;
    current *= x * x * (-1);
    return current;
}

double row(double row_(int n, double x, double current), double epsilon, double x)
{
    double value_current = row_(0, x, 0);
    double value_next = row_(1, x, value_current);
    int n = 1;
    while(fabs(value_next) > epsilon)
    {
        n++;
        value_current += value_next;
        value_next = row_(n, x, value_next);
    }
    return value_next + value_current;
}