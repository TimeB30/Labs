#ifndef LAB_1_3_FUNCTIONS_H
#define LAB_1_3_FUNCTIONS_H

#define EQUATION_COEFFICIENTS 3
#define ROOTS 2

#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

double binary_power(double base, unsigned long long exponent);
double root_of_power(double x, int exponent, double eps);

int check_flag(char** word);
int is_number(const char* string);
int check_double(char** word);
void swap(double *a, double *b);
int partition(double** array, int low, int high, double epsilon);
void quicksort(double** array, int low, int high, double epsilon);
int generate_permutation(double** array, int array_length, double epsilon);
int solve_equation(double** permutation, double** solutions, int amount_of_solutions, double epsilon);


#endif //LAB_1_3_FUNCTIONS_H
