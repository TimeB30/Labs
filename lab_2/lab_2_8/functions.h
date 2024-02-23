#ifndef LAB_2_8_FUNCTIONS_H
#define LAB_2_8_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

enum exit_codes
{
    memory_fail,
    success,
    local_error,
    wrong_system,
};

int string_length(char** string);
int long_arithmetic_addition(int base, char** result, char** to_add);
int to_number(char modulo);
int to_ascii(char modulo);
int reverse(char** to_reverse);
int add_up_strings(char** result, int base, int amount, ...);

#endif //LAB_2_8_FUNCTIONS_H
