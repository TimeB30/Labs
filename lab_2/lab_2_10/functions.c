#include "functions.h"


double factorial(unsigned int n)
{
    if(n <= 1) return 1;
    return factorial(n-1)*n;
}

double combinations(unsigned int n, unsigned int k)
{
    return factorial(n) / (factorial(n-k) * factorial(k));
}

void coefficients(unsigned int n, double** array_of_coeffs)
{
    for(int k = 0; k <= n; k++) (*array_of_coeffs)[k] = combinations(n, k);
}

double binary_power(double base, unsigned long long exponent)
{
    double v = 1.0;
    while(exponent)
    {
        if(exponent & 1) v *= base;
        base *= base;
        exponent >>= 1;
    }
    return v;
}

int polynomial_recomposition(double a, double** array_of_coeffs, int exponent, ...)
{
    *array_of_coeffs = (double*)malloc(sizeof(double)*(exponent+1));
    if(*array_of_coeffs == NULL) return memory_error;

    double* original_coefficients = (double*)malloc(sizeof(double)*(exponent + 1));
    if(original_coefficients == NULL) { free(array_of_coeffs); return memory_error; }

    va_list args;
    va_start(args, exponent);
    for(int i = exponent; i >= 0; i--) original_coefficients[i] = va_arg(args, double);
    va_end(args);

    coefficients(exponent, array_of_coeffs);
    for(int i = 0; i <= exponent; i++) (*array_of_coeffs)[i] *= binary_power(a, i) * original_coefficients[0];
    for(int i = 1; i <= exponent; i++)
    {
        double next = original_coefficients[i] - (*array_of_coeffs)[i];
        double* current_poly = (double*)malloc(sizeof(double) * (exponent - i + 1));
        if(current_poly == NULL)
        {
            free(array_of_coeffs);
            free(original_coefficients);
            return memory_error;
        }

        coefficients(exponent - i, &current_poly);
        for(int j = 0; j <= exponent; j++) current_poly[j] *= next * binary_power(a,j);

        (*array_of_coeffs)[i] = current_poly[0];
        for(int j = i + 1; j <= exponent; j++) (*array_of_coeffs)[j] += current_poly[j - i];
        free(current_poly);
    }
    free(original_coefficients);
    return success;
}