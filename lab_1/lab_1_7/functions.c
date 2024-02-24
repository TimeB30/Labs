
#include "functions.h"

bool check_flag(char** word)
{
    size_t length = strlen(*word);
    if(((*word)[0] != '-' && (*word)[0] != '/')) return false;
    if(length != 2) return false;
    return true;
}


void skip_splits(FILE** file, int* c)
{
    while(*c == '\n' || *c == ' ' || *c == '\t')
    {
        if(*c == EOF) break;
        *c = fgetc(*file);
    }
}

int write_from_to(FILE** input, FILE** output, int* c)
{
    while(*c != ' ' && *c != '\n' && *c != '\t' && *c != EOF)
    {
        if(fprintf(*output, "%c", *c) == EOF) return writing_fail;
        *c = fgetc(*input);
    }
    if(fprintf(*output, " ") == EOF) return writing_fail;
    return writing_success;
}


int even_odd_term_writing(FILE** input1, FILE** input2, FILE** output)
{
    int i = 1;
    int c1 = fgetc(*input1);
    int c2 = fgetc(*input2);

    while(c1 != EOF && c2 != EOF)
    {
        if(i % 2 == 1)
        {
            skip_splits(input1, &c1);
            if(write_from_to(input1, output, &c1) == writing_fail) return writing_fail;
            skip_splits(input1, &c1);

        }
        else
        {
            skip_splits(input1, &c1);
            if(write_from_to(input2, output, &c2) == writing_fail) return writing_fail;
            skip_splits(input2, &c2);
        }
        i++;
    }
    if(c1 == EOF) {
        while(c2 != EOF)
        {
            skip_splits(input1, &c1);
            if(write_from_to(input2, output, &c2) == writing_fail) return writing_fail;
            skip_splits(input2, &c2);
        }
    }
    else
    {
        while(c1 != EOF)
        {
            skip_splits(input1, &c1);
            if(write_from_to(input1, output, &c1) == writing_fail) return writing_fail;
            skip_splits(input1, &c1);
        }
    }
    if(fprintf(*output, "%c", EOF) == EOF) return writing_fail;
    return writing_success;
}

int write_with_lowering(FILE** input, FILE** output, int* c)
{
    while(*c != ' ' && *c != '\n' && *c != '\t' && *c != EOF)
    {
        if(fprintf(*output, "%c", tolower(*c)) == EOF) return writing_fail;
        *c = fgetc(*input);
    }
    if(fprintf(*output, " ") == EOF) return writing_fail;
    return writing_success;
}

char digit(int modulo)
{
    if(modulo > 9) return (modulo + 'A' - 10);
    return (modulo + '0');
}

int to_system(int value, char** destination, int base)
{

    int length = floor(log(value)/log(base)) + 2;
    *destination = (char*)malloc(sizeof(char)*length);
    if(destination == NULL) return m_alloc_fail;
    for(int i = length - 2; i >= 0; i--)
    {
        (*destination)[i] = digit(value % base);
        value /= base;
    }
    (*destination)[length-1] = '\0';
    return success;
}

int write_ascii(FILE** input, FILE** output, int* c, int base)
{
    while(*c != ' ' && *c != '\n' && *c != '\t' && *c != EOF)
    {
        char* ptr;
        if(to_system(*c, &ptr, base) == m_alloc_fail) return m_alloc_fail;
        if(fprintf(*output, "%s", itoa(*c, ptr, base)) == EOF) return writing_fail;
        *c = fgetc(*input);
    }
    if(fprintf(*output, " ") == EOF) return writing_fail;
    return writing_success;
}

int letters_to_ascii(FILE** input, FILE** output)
{
    int i = 1;
    int c = fgetc(*input);

    while(c != EOF){

        if(i % 10 != 0 && i % 2 == 0)
        {
            skip_splits(input, &c);
            if(write_with_lowering(input, output, &c) == writing_fail) return writing_fail;
            skip_splits(input, &c);
        }
        else if(i % 10 != 0 && i % 5 == 0)
        {
            skip_splits(input, &c);
            if(write_ascii(input, output, &c, 8) == writing_fail) return writing_fail;
            skip_splits(input, &c);
        }
        else if(i % 10 == 0)
        {
            skip_splits(input, &c);
            if(write_ascii(input, output, &c, 4) == writing_fail) return writing_fail;
            skip_splits(input, &c);
        }
        else
        {
            skip_splits(input, &c);
            if( write_from_to(input, output, &c) == writing_fail) return writing_fail;
            skip_splits(input, &c);
        }
        i++;
    }
    return writing_success;
}
