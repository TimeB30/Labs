#ifndef LAB_2_10_FUNCTIONS_H
#define LAB_2_10_FUNCTIONS_H

#include <stdlib.h>
#include <stdarg.h>

enum exit_codes
{
    memory_error,
    success,
};

double factorial(unsigned int n);
double combinations(unsigned int n, unsigned int k);
void coefficients(unsigned int n, double** array_of_coeffs);
double binary_power(double base, unsigned long long exponent);
int polynomial_recomposition(double a, double** array_of_coeffs, int exponent, ...);

#endif //LAB_2_10_FUNCTIONS_H