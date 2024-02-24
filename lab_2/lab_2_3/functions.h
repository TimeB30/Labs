
#ifndef LAB_2_3_FUNCTIONS_H
#define LAB_2_3_FUNCTIONS_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

enum exit_codes
{
    memory_error,
    file_opening_error,
    success,
};

typedef struct line_pos
{
    int line;
    int pos;
} strct;

int string_length(char** string);
int naive_search(strct*** results, char* pattern, int texts, ...);


#endif //LAB_2_3_FUNCTIONS_H
