
#ifndef CLIONPROJECTS_FUNCTIONS_H
#define CLIONPROJECTS_FUNCTIONS_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int is_number(const char* string);
int is_prime(int number);

void multiples(int number, int** array, int* amount);
void create_table_of_powers(int exponent, long long int*** table);
void print_table_of_powers(int exponent, long long int*** table);
void long_arithmetics_multiplication(int x, char** result, size_t* length);
void factorial(int given_number, char** result, size_t* result_size);
size_t stirling_formula(int n);

#endif //CLIONPROJECTS_FUNCTIONS_H
