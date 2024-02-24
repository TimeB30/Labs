
#include "functions.h"



int exclude_arabic_digits(FILE** origin, FILE** destination)
{
    int c;
    while((c = fgetc(*origin)) != EOF)
    {
        if(!isdigit(c) || c == EOF)
        {
            if(fputc(c, *destination) == EOF) return writing_fail;
        }
    }
    return writing_success;
}

int count_latin_letters(FILE** origin, FILE** destination)
{
    int c = '1';
    int counter = 0;
    while(c != EOF){
        c = fgetc(*origin);
        if(isalpha(c))
        {
            counter++;
        }
        else if(c == '\n' || c == EOF)
        {
            if(!fprintf(*destination, "%d\n", counter)) return writing_fail;
            counter = 0;
        }
    }
    return writing_success;
}

int count_non_latin_arabic(FILE** origin, FILE** destination)
{
    int c = '1';
    int counter = 0;
    while(c != EOF)
    {
        c = fgetc(*origin);
        if(!(isalnum(c))  && c != ' ' && c != '\n' && c != '\t' && c != EOF)
        {
            counter++;
        }
        else if(c == '\n' || c == EOF)
        {
            if(!fprintf(*destination, "%d\n", counter)) return writing_fail;
            counter = 0;
        }
    }
    return writing_success;
}

int swap_with_ascii16(FILE** origin, FILE** destination)
{
    int c;
    while((c = fgetc(*origin)) != EOF)
    {
        if(!isalpha(c))
        {
            if(c == '\n' || c == EOF)
            {
                if(fprintf(*destination, "\n") == EOF) return writing_fail;
            }
            else
            {
                if(fprintf(*destination, "%X", c) == EOF) return writing_fail;
            }
        }
        else
        {
            if(fprintf(*destination, "%c", c) == EOF) return writing_fail;
        }
    }
    return writing_success;
}

int find_dash(char** path, size_t length)
{
    for(int i = length; i >= 0; i--)
    {
        if((*path)[i] == '\\')
        {
            return i;
        }
    }
    return -1;
}

bool check_flag(char** word)
{
    size_t length = strlen(*word);
    if(((*word)[0] != '-' && (*word)[0] != '/')) return false;
    if(length == 3 && (*word)[1] != 'n') return false;
    return true;
}