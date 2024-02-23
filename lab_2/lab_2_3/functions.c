#include "functions.h"

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

int naive_search(strct*** results, char* pattern, int texts, ...)
{
    va_list args;
    va_start(args, texts);
    int pattern_length = string_length(&pattern);
    *results = (strct**)malloc(sizeof(strct*)*texts);

    for(int i = 0; i < texts; i++) {
        char *path = va_arg(args, char*);
        FILE *source = fopen(path, "r");
        if (source == NULL) return file_opening_error;

        (*results)[i] = (strct*)malloc(sizeof(strct)*1);
        int capacity = 1;
        int line = 1;
        int position = 1;
        int flag = 1;
        int count = 0;
        char c = '1';

        if(pattern_length == 0)
        {
            while(!feof(source))
            {
                c = fgetc(source);
                count++;
                if(capacity == count)
                {
                    capacity *= 2;
                    strct* for_realloc = realloc((*results)[i], sizeof(strct)*capacity);
                    if( for_realloc == NULL)
                    {
                        for(int j = 0; j < i; j++)
                        {
                            free((*results)[j]);
                        }
                        free(*results);
                        return memory_error;
                    }
                    (*results)[i] = for_realloc;
                }
                (*results)[i][count] = (strct){0, 0};
                (*results)[i][count-1] = (strct){line, position};
                if(c == '\n') {position = 1; line++;}
                else position++;
            }
            return success;
        }

        while(c != EOF)
        {
            flag = 1;
            for(int j = 0; j < pattern_length; j++)
            {
                c = fgetc(source);
                if(c != pattern[j])
                {
                    if(j > 0 && c == pattern[j-1])
                    {
                        fseek(source, -pattern_length + 1, SEEK_CUR);
                        position--;
                    }
                    position += j;
                    flag = 0;
                    if(c == '\n') { line++; position = 1; }
                    if(c == EOF)
                    {
                        if(capacity == count)
                        {
                            capacity += 1;
                            strct* for_realloc = realloc((*results)[i], sizeof(strct)*capacity);
                            if( for_realloc == NULL)
                            {
                                for(int k = 0; k < i; k++)
                                {
                                    free((*results)[k]);
                                }
                                free(*results);
                                return memory_error;
                            }
                            (*results)[count-1] = for_realloc;
                        }
                        (*results)[i][count] = (strct){0, 0};
                    }
                    break;
                }
            }
            if(flag == 1)
            {
                count++;
                if(capacity == count)
                {
                    capacity *= 2;
                    strct* for_realloc = realloc((*results)[i], sizeof(strct)*capacity);
                    if( for_realloc == NULL)
                    {
                        for(int j = 0; j < i; j++)
                        {
                            free((*results)[j]);
                        }
                        free(*results);
                        return memory_error;
                    }
                    (*results)[i] = for_realloc;
                }
                (*results)[i][count-1] = (strct){line, position};
                fseek(source, -pattern_length + 1, SEEK_CUR);
                position += pattern_length - 1;
            }
        }
        fclose(source);
    }

    va_end(args);
    return success;
}