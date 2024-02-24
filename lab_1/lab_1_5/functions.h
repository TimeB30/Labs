
#ifndef LAB_1_5_FUNCTIONS_H
#define LAB_1_5_FUNCTIONS_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

enum double_codes
{
    positive,
    negative_or_zero,
    not_a_number
};
int check_double(char** word);

double row_a(int n, double x, double current);
double row_b(int n, double x, double current);
double row_c(int n, double x, double current);
double row_d(int n, double x, double current);
double row(double row_(int n, double x, double current), double epsilon, double x);
#endif //LAB_1_5_FUNCTIONS_H
