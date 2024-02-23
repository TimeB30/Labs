#ifndef LAB_1_7_FUNCTIONS_H
#define LAB_1_7_FUNCTIONS_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

enum exit_codes
{
    writing_fail,
    writing_success,
    m_alloc_fail,
    success,
};

bool check_flag(char** word);

void skip_splits(FILE** file, int* c);
int write_from_to(FILE** input, FILE** output, int* c);

int even_odd_term_writing(FILE** input1, FILE** input2, FILE** output);
int letters_to_ascii(FILE** input, FILE** output);

int to_system(int value, char** destination, int base);
char digit(int modulo);

#endif //LAB_1_7_FUNCTIONS_H
