
#include "functions.h"

int string_length(char** string)
{
    int count = 0;
    while((*string)[count] != '\0')
    {
        count++;
    }
    return count;
}

int to_number(char modulo)
{
    if(isalpha(modulo)) return toupper(modulo) - 'A' + 10;
    else if(isdigit(modulo)) return modulo - '0';
    else return 0;
}

int to_ascii(char modulo)
{
    if(modulo > 9) return modulo + 'A' - 10;
    else return modulo + '0';
}

int reverse(char** to_reverse)
{
    size_t length = string_length(to_reverse);
    char* result = (char*)malloc(sizeof(char)*(length+1));
    if(result == NULL)
    {
        return memory_fail;
    }
    for(int i = 0; i < length; i++)
    {
        result[i] = (*to_reverse)[length-i-1];
    }
    result[length] = '\0';
    *to_reverse = result;
    return success;
}

int check_system(char c, int base)
{
    if(to_number(c) >= base) return wrong_system;
    return success;
}

int long_arithmetic_addition(int base, char** result, char** to_add)
{
    int length_to_add = string_length(to_add);
    int length_result = string_length(result);
    int len_max = length_result > length_to_add ? length_result : length_to_add;

    char* for_realloc;
    for_realloc = (char*)calloc(len_max+1, sizeof(char));
    if(for_realloc == NULL)
    {
        free(*result);
        return memory_fail;
    }
    strcpy(for_realloc, *result);
    *result = for_realloc;
    int carry = 0;
    for(int i = 0; i < len_max; i++)
    {
        if(check_system((*to_add)[i], base) == wrong_system)
        {
            free(*result);
            return wrong_system;
        }
        int digit = to_number((*result)[i]) + to_number((*to_add)[i]);

        (*result)[i] = to_ascii((digit+carry) % base);
        carry = (digit+carry) / base;
    }

    while(carry > 0)
    {
        (*result)[len_max] = to_ascii(carry % base);
        len_max++;
        carry /= base;
    }
    (*result)[len_max] = '\0';

    return success;
}

int add_up_strings(char** result, int base, int amount, ...)
{
    if(base < 2 || base > 36) return local_error;

    va_list args;
    va_start(args, amount);
    for(int i = 0; i < amount; i++)
    {
        char* to_add = va_arg(args, char*);
        reverse(&to_add);
        if(long_arithmetic_addition(base, result, &to_add) == wrong_system)
        {
            return wrong_system;
        }
    }
    reverse(result);
    return success;
}