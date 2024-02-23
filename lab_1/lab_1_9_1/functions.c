#include "functions.h"

bool is_number(const char* string)
{
    size_t string_length = strlen(string);
    int i = 0;
    if(string[0] == '-') i = 1;
    for(; i < string_length; i++)
    {
        if(!isdigit(string[i])) return false;
    }
    return true;
}


void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}