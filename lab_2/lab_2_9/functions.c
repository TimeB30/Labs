

#include "functions.h"
#define ITERATIONS_MAX 50

int is_final(double epsilon, int system, char*** results, int amount, ...)
{
    va_list args;
    va_start(args, amount);
    *results = (char**)malloc(sizeof(char*)*amount);
    if(*results == NULL) return memory_error;

    double number;

    for(int i = 0; i < amount; i++)
    {
        int length = 2;
        int capacity = 4;
        (*results)[i] = (char*)malloc(sizeof(char)*(length+1));
        if((*results)[i] == NULL)
        {
            for(int j = 0; j <= i; j++)
            {
                free((*results)[j]);
            }
            free(*results);
            return memory_error;
        }
        (*results)[i][0] = '0';
        (*results)[i][1] = '.';
        (*results)[i][2] = '\0';
        number = va_arg(args, double);
        double fraction = number;

        int iterations = 0;
        while(fraction > epsilon)
        {
            if(iterations == ITERATIONS_MAX)
            {
                free((*results)[i]);
                (*results)[i] = "Unrepresentable\0";
                break;
            }
            length++;
            if(capacity == length+1)
            {
                capacity *= 2;
                char* for_realloc;
                for_realloc = (char*)realloc((*results)[i], sizeof(char)*capacity);
                if(for_realloc == NULL)
                {
                    free(*results);
                    return memory_error;
                }
                (*results)[i] = for_realloc;
            }
            fraction *= system;
            int digit = (int)fraction;
            fraction -= (int)fraction;
            (*results)[i][length-1] = (digit < 10) ? digit + '0' : digit + 'A' - 10;
            (*results)[i][length] = '\0';
            iterations++;
        }
    }
    return success;
}