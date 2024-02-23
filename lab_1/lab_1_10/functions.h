#ifndef LAB_1_10_FUNCTIONS_H
#define LAB_1_10_FUNCTIONS_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

enum exit_codes
{
    not_a_number = -1,
    memory_fail,
    success,
};
int to_decimal(char** string, int length, int base, int* sign);
int get_string(char** string, int* length);

int to_system(int value, char** destination, int base);
char digit(int modulo);

#endif //LAB_1_10_FUNCTIONS_H
