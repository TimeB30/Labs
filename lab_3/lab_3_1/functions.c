
#include "functions.h"
#include <stdlib.h>

void remove_trailing_zeroes(char** string)
{
    for(;**string == '0'; (*string)++);
}

int to_system(char** result, unsigned int n, int exponent)
{
    int result_length = sizeof(unsigned int) / exponent + 3;
    (*result) = (char*)malloc(sizeof(char) * (result_length + 1));
    if(*result == NULL) return memory_error;

    int group_rang = 1 << exponent;

    for(int i = result_length - 1; i >= 0; i--)
    {
        int group = n & 1;
        for(int j = 2; j < group_rang; j<<=1)
        {
            group |= n & j;
        }
        if(group < 10) (*result)[i] = group + '0';
        else (*result)[i] = group - 10 + 'a';
        n >>= exponent;
    }
    (*result)[result_length] = '\0';
    remove_trailing_zeroes(result);
    return success;
}