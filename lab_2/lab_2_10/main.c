#include "functions.h"
#include <stdio.h>

int main()
{
    int pow = 2;
    double a = -1.0;
    double* array_of_coeffs;
    //x^2 + 3x + 10 = 1*(x-1)^2 + 5*(x-1)^1 + 14*(x-1)^0
    if(polynomial_recomposition(a, &array_of_coeffs, pow, 2.0, 1.0, 1.0) == memory_error)
    {
        printf("Memory error\n");
        return 0;
    }
    for(int i = 0; i <= pow; i++)
    {
        printf("+ %.2f * (x + %.2f)^%d ", array_of_coeffs[pow - i], a, i);
    }
    free(array_of_coeffs);
    return 0;
}