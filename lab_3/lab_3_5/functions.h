
#ifndef LAB_3_5_FUNCTIONS_H
#define LAB_3_5_FUNCTIONS_H

#include "_string.h"
#include <ctype.h>
#include <string.h>

struct Student
{
    unsigned int id;
    struct String first_name;
    struct String last_name;
    struct String group;
    unsigned char* marks;
};

enum command_codes
{
    print,
    trace,
    sort,
    find,
    higraders,
    quit,
    unknown
};

int is_correct_word(char* string);
int is_number(const char* string);
int get_string(FILE* stream, char** string, int* length);

int write_to_file(const struct Student* student, FILE* dest);
int read_from_file(FILE* source, struct Student** students, size_t* size);

int sort_students(struct Student** students, size_t amount, const char* field);
int compare_id(const void* number1, const void* number2);
int compare_group(const void* str1, const void* str2);
int compare_firstname(const void* str1, const void* str2);
int compare_lastname(const void* str1, const void* str2);

int search_for_student(struct Student** students, int students_amount, const char* field, const char* tofind, int* amount, struct Student** results);
int find_id(struct Student** students, int students_amount, const char* tofind, struct Student** results, int* amount);
int find_lastname(struct Student** students, int students_amount, const char* tofind, struct Student** results, int* amount);
int find_firstname(struct Student** students, int students_amount, const char* tofind, struct Student** results, int* amount);
int find_group(struct Student** students, int students_amount, const char* tofind, struct Student** results, int* amount);

double get_avg_all(struct Student** students, int amount);
double get_avg_one(struct Student*);

int dialogue(const char* input_path, int argc, const char** argv);

#endif //LAB_3_5_FUNCTIONS_H
