
#include "functions.h"

void skip_splits(FILE** file, int* c)
{
    while(*c == '\n' || *c == ' ' || *c == '\t')
    {
        if(*c == EOF) break;
        *c = fgetc(*file);
    }
    fseek(*file, -1, SEEK_CUR);
}

int notation(char** string, int length)
{
    int c;
    int base = 0;
    for(int i = 0; i < length; i++)
    {
        c = (*string)[i];
        if(isdigit(c))
        {
            base = (base < c - '0' + 1) ? c - '0' + 1 : base;
        }
        else if(isalpha(c))
        {
            base = (base < tolower(c) - 'a' + 11) ? tolower(c) - 'a' + 11 : base;
        }
        else
        {
            return 0;
        }
    }
    return (base > 1) ? base : 0;
}

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
    int result = 0;
    int next;
    for(int i = 0; i < length; i++)
    {
        char c = tolower((*string)[i]);
        if(!isalnum(c))
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

int get_string(char** string, int* c, int* length, FILE* file)
{
    *length = 0;
    int capacity = 1;
    char* for_realloc;
    *c = fgetc(file);
    *string = (char*)malloc(sizeof(char)*1);
    if(*string == NULL) return memory_fail;
    while(*c != '\n' && *c != EOF && *c != '\t' && *c != ' ')
    {
        (*string)[(*length)++] = *c;
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
        *c = fgetc(file);
    }
    (*string)[*length] = '\0';
    return success;
}