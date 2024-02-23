#ifndef LAB_3_4_FUNCTIONS_H
#define LAB_3_4_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>



struct String
{
    char* string;
    int length;
};

struct String* create_String(const char* string);
int clear_string(struct String* s);
int compare_strings(struct String* s1, struct String* s2);
int are_equal(struct String* s1, struct String* s2);
int copy(struct String* from, struct String** to);
struct String* copy_to_new(struct String* string);
int concat_strings(struct String* to, struct String* from);

#endif //LAB_3_4_FUNCTIONS_H
