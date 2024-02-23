#ifndef LAB_1_4_FUNCTIONS_H
#define LAB_1_4_FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <stdbool.h>

enum exit_codes
{
    writing_fail,
    writing_success,
};

int exclude_arabic_digits(FILE** origin, FILE** destination);
int count_latin_letters(FILE** origin, FILE** destination);
int count_non_latin_arabic(FILE** origin, FILE** destination);
int swap_with_ascii16(FILE** origin, FILE** destination);

int find_dash(char** path, size_t length);
bool check_flag(char** word);

#endif //LAB_1_4_FUNCTIONS_H
