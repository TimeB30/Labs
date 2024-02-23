#ifndef LAB_3_3_FUNCTIONS_H
#define LAB_3_3_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>


typedef struct Employee
{
    unsigned int id;
    char* first_name;
    char* last_name;
    double wage;
} Employee;

enum exit_codes
{
    memory_error,
    success,
    invalid_file_content,
    unexpected,
    eof_reached,
    endl_reached,
    newline_reached,
    space_reached,
    input_invalid,
};

int get_string(FILE* stream, char** string, int* length);
int is_number(const char* string);
int is_correct_word(char* string);

int64_t to_int64(double x);
int cmp_double(double x1, double x2);
int a_compare(const void* employee_1, const void* employee_2);
int d_compare(const void* employee_1, const void* employee_2);

int read_from_file(FILE* source, struct Employee** employees, size_t* size);
int write_to_file(const struct Employee* employee, FILE* dest);
#endif //LAB_3_3_FUNCTIONS_H
