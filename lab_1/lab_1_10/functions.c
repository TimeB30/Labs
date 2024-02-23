#include "functions.h"

int to_decimal(char** string, int length, int base, int* sign)
{
    if((*string)[0] == '-')
    {
        (*string)++;
        length--;
        *sign = -1;
    }
    else
    {
        *sign = 1;
    }
    while((*string)[0] == '0')
    {
        (*string)++;
        length--;
    }
    if(length == 0) return 0;
    int result = 0;
    int next;
    for(int i = 0; i < length; i++)
    {
        char c = (*string)[i];
        if(!isalnum(c) || tolower(c) != c)
        {
            return not_a_number;
        }
        if(isalpha(c)) next = c - 'a' + 10;
        else
        {
            next = c - '0';
        }
        if (next > base) return not_a_number;
        result = result * base + next;
    }

    return result;
}

int get_string(char** string, int* length)
{
    *length = 0;
    int capacity = 1;
    char* for_realloc;
    int c = getchar();
    *string = (char*)malloc(sizeof(char)*1);
    if(*string == NULL) return memory_fail;
    while(c != '\n' && c != '\0' && c != '\t' && c != ' ')
    {
        (*string)[(*length)++] = c;
        if(*length >= capacity)
        {
            capacity *= 2;
            for_realloc = realloc(*string, capacity * sizeof(char));
            if(for_realloc == NULL)
            {
                free(*string);
                return memory_fail;
            }
            *string = for_realloc;
        }
        c = getchar();
    }
    (*string)[*length] = '\0';
    return success;
}

char digit(int modulo)
{
    switch (modulo)
    {
        case 0: return '0';        case 1: return '1';        case 2: return '2';
        case 3: return '3';        case 4: return '4';        case 5: return '5';
        case 6: return '6';        case 7: return '7';        case 8: return '8';
        case 9: return '9';        case 10: return 'A';        case 11: return 'B';
        case 12: return 'C';        case 13: return 'D';        case 14: return 'E';
        case 15: return 'F';        case 16: return 'G';        case 17: return 'H';
        case 18: return 'I';        case 19: return 'J';        case 20: return 'K';
        case 21: return 'L';        case 22: return 'M';        case 23: return 'N';
        case 24: return 'O';        case 25: return 'P';        case 26: return 'Q';
        case 27: return 'R';        case 28: return 'S';        case 29: return 'T';
        case 30: return 'U';        case 31: return 'V';        case 32: return 'W';
        case 33: return 'X';        case 34: return 'Y';        case 35: return 'Z';
        default: return 0;
    }
}

int to_system(int value, char** destination, int base)
{
    if (value == 0)
    {
        *destination = (char*)malloc(sizeof(char)*1);
        if(*destination == NULL) return memory_fail;
        (*destination)[0] = '0';
        (*destination)[1] = '\0';
        return success;
    }
    int length = floor(log(value)/log(base)) + 2;
    *destination = (char*)malloc(sizeof(char)*length);
    if(destination == NULL) return memory_fail;
    for(int i = length - 2; i >= 0; i--)
    {
        (*destination)[i] = digit(value % base);
        value /= base;
    }
    (*destination)[length-1] = '\0';
    return success;
}