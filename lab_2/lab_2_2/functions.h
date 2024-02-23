#ifndef LAB_2_2_FUNCTIONS_H
#define LAB_2_2_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

enum exit_codes
{
    SUCCESS,
};

double binary_power_recursive (double base, unsigned long long exponent);
double binary_power(double base, unsigned long long exponent);
void binary(double base, unsigned long long exponent, double** results);
double old_approximate_power(double base, double exponent);
double root_of_power(double x, int exponent, double eps);

int avg_geometric(double epsilon, double** results, int count, ...);

#endif //LAB_2_2_FUNCTIONS_H
