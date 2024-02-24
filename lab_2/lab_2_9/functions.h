

#ifndef LAB_2_9_FUNCTIONS_H
#define LAB_2_9_FUNCTIONS_H

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>

enum exit_codes
{
    memory_error,
    success,
};
int is_final(double epsilon, int system, char*** results, int amount, ...);

#endif //LAB_2_9_FUNCTIONS_H
