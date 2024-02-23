#ifndef LAB_2_1_FUNCTIONS_H
#define LAB_2_1_FUNCTIONS_H

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

enum exit_codes
{
    memory_error,
    not_a_number,
    number,
    success,
};

int check_flag(char** word);
int is_number(const char* string);
int string_length(char** str);
int reverse_str(char** string, char** result);
int odd_to_upper(char** origin, char** result);
int concatenate(char** string_first, char** result);

#endif //LAB_2_1_FUNCTIONS_H
