
#include "functions.h"

int compare(int* a, int* b)
{
    if(*a < *b) return -1;
    if(*a == *b) return 0;
    return 1;
}

int find_nearest(int** origin, int length, int value)
{

    int a = 0;
    int b = length;
    int middle = -1;

    while (middle != (a + b)/2)
    {
        middle = (a+b)/2;
        if((*origin)[middle] == value)
        {
            return value;
        }
        if((*origin)[middle] < value)
        {
            a = middle;
            continue;
        }
        else
        {
            b = middle;
            continue;
        }
    }
    return (*origin)[middle];
}