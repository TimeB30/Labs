
#ifndef LAB_1_6_FUNCTIONS_H
#define LAB_1_6_FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

enum double_codes
{
    positive,
    negative_or_zero,
    not_a_number
};

double old_approximate_power(double base, double exponent);
int check_double(char** word);

double task_a(double x);
double task_b(double x);
double task_c(double x);
double task_d(double x);
double trapezoid(double function(double), double a, double b,double epsilon);

#endif //LAB_1_6_FUNCTIONS_H
