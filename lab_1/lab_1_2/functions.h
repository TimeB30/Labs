
#ifndef LAB_1_2_FUNCTIONS_H
#define LAB_1_2_FUNCTIONS_H

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

double binary_power(double base, unsigned long long exponent);
double old_approximate_power(double base, double exponent);
double root_of_power(double x, int exponent, double eps);
double row_one_over_n(double n);
int is_prime(int number);

double lim_e(double eps, int n);
double lim_pi(double eps, int n);
double lim_ln2(double eps, int n);
double lim_sqrt2(double eps);
double lim_gamma(double eps, int n);
double lim(double (*limit)(double, int), double epsilon);

double row_e(double eps, int n);
double row_pi(double eps, int n);
double row_ln2(double eps, int n);
double row_sqrt2(double eps, int n);
double row_gamma(double eps, int n);
double row(double(*row_)(double, int), double epsilon);

double eq_e(double argument, double eps);
double eq_pi(double argument, double eps);
double eq_ln2(double argument, double eps);
double eq_sqrt2(double argument, double eps);
double eq(double(*eq_)(double, double), double epsilon);

double eq_gamma(double epsilon);

#endif //LAB_1_2_FUNCTIONS_H
