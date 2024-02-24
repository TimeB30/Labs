
#ifndef LAB_3_9_FUNCTIONS_H
#define LAB_3_9_FUNCTIONS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "tree.h"

enum cmd_codes
{
    find,
    shortest,
    longest,
    common,
    print,
    save,
    load,
    height,
    quit,
    unknown,
};

enum get_string_exit_codes
{
    endl_reached,
    newline_reached,
    eof_reached,
    space_reached,
};

int get_string(FILE* stream, char** string, int* length, const char* separators);
int read_from_file(FILE* stream, struct Node* head, char* separators);
int get_cmd_code(const char* command);
int is_number(const char* string);
int save_to(FILE* dest, struct Node* tree);
int load_from(FILE* origin, struct Node* tree);


#endif //LAB_3_9_FUNCTIONS_H
