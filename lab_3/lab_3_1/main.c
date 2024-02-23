#include "functions.h"
#include <stdio.h>
#define SYSTEM_EXP 2
#define NUMBER 100


int main()
{
    char* result;
    to_system(&result, NUMBER, SYSTEM_EXP);
    printf("%s", result);

}