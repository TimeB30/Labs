
#include "functions.h"

int check_flag(char** word)
{
    if(((*word)[0] != '-' && (*word)[0] != '/') || (*word)[2] != '\0') return 0;
    return 1;
}

int string_length(char** string)
{
    if(*string == NULL) return 0;
    int count = 0;
    while((*string)[count] != '\0')
    {
        count++;
    }
    return count;
}

int is_number(const char* string){
    size_t string_length_ = string_length(&string);
    int i = 0;
    if((string)[0] == '-'){
        i = 1;
    }
    for( ; i < string_length_; i++){
        if(!isdigit(string[i])) return not_a_number;
    }
    return number;
}


int reverse_str(char** string, char** result)
{
    int count = string_length(string);
    *result = (char*)malloc(sizeof(char)*(count+1));
    if(*result == NULL)
    {
        return memory_error;
    }
    for(int i = 0; i < count; i++)
    {
        (*result)[i] = (*string)[count-i-1];
    }
    (*result)[count] = '\0';
    return success;
}

int odd_to_upper(char** origin, char** result)
{
    int count = string_length(origin);
    *result = (char*)malloc(sizeof(char)*(count+1));
    if (*result == NULL)
    {
        return memory_error;
    }
    for(int i = 0; i < count; i++)
    {
        (*result)[i] = (i%2 == 0) ? (*origin)[i] : toupper((*origin)[i]);
    }
    (*result)[count] = '\0';
    return success;
}

int concatenate(char** string_first, char** result)
{
    while(**string_first != '\0')
    {
        **result = **string_first;
        (*string_first)++;
        (*result)++;
    }
    return success;
}