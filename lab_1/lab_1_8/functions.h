
#ifndef LAB_1_8_FUNCTIONS_H
#define LAB_1_8_FUNCTIONS_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

enum exit_codes
{
    not_a_number = -1,
    memory_fail,
    success,
};
void skip_splits(FILE** file, int* c);

int get_string(char** string, int* c, int* length, FILE* file);
int to_decimal(char** string, int length, int base, int* sign);
int notation(char** string, int length);

#endif //LAB_1_8_FUNCTIONS_H
