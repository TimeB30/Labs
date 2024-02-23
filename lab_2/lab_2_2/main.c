#include "functions.h"
#define EPSILON 1e-10
#define BASE 2.718281828
#define EXPONENT 2

int main()
{

    double precision = 1.0/EPSILON;
    double x = 0;
    double x2 = 0;
    double x3 = 0;
    double f = 0;
    double f2 = 0;
    double f3 = 0;

    double* results_for_binary = (double*)malloc(sizeof(double) * 3);
    if(results_for_binary == NULL)
    {
        printf("Memory error:/\n");
        return 1;
    }

    double* results_for_non_integer_exponent = (double*)malloc(sizeof(double) * 3);
    if(results_for_non_integer_exponent == NULL)
    {
        printf("Memory error:/\n");
        return 1;
    }

    binary(BASE, EXPONENT, &results_for_binary);

    x = floor(results_for_binary[0]*precision)/precision;
    x2 = floor(results_for_binary[1]*precision)/precision;
    x3 = floor(results_for_binary[2]*precision)/precision;

    printf("Calculating with binary exponentiation\n"
           "Result of using:\n"
           "Recursive function      Non-recursive function      pow()\n"
           "%g                 %g                     %g\n", x, x2, x3);

    if(avg_geometric(EPSILON, &results_for_non_integer_exponent, 3, 1.0, 2.0, 3.0) == SUCCESS)
    {
        f = floor(results_for_non_integer_exponent[0]*precision)/precision;
        f2 = floor(results_for_non_integer_exponent[1]*precision)/precision;
        f3 = floor(results_for_non_integer_exponent[2]*precision)/precision;
        printf("Average geometric calculated with:\n"
               "Algorithm of searching root of exponent     Old Approximation Algorithm     pow()\n"
               "%g                                     %g                         %g", f, f2, f3);
        return 0;
    }
    else
    {
        printf("bro how");
        return 1;
    }
}
