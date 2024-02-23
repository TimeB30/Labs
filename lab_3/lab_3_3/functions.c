#include "functions.h"

int get_string(FILE* stream, char** string, int* length)
{
    *length = 0;
    int capacity = 1;
    char* for_realloc;
    int c = fgetc(stream);
    *string = (char*)malloc(sizeof(char)*1);
    if(*string == NULL) return memory_error;
    while(c != '\n' && c != '\0' && c != '\t' && c != ' ' && c != EOF)
    {
        (*string)[(*length)++] = c;
        if(*length >= capacity)
        {
            capacity *= 2;
            for_realloc = realloc(*string, capacity * sizeof(char));
            if(for_realloc == NULL)
            {
                free(*string);
                return memory_error;
            }
            *string = for_realloc;
        }
        c = fgetc(stream);
    }
    (*string)[*length] = '\0';
    if(c == ' ') return space_reached;
    if (c == EOF) return eof_reached;
    if (c == '\n') return newline_reached;
    if (c == '\0') return endl_reached;
    return success;
}

int is_number(const char* string)
{
    size_t string_length = strlen(string);
    for(int i = 0; i < string_length; i++){
        if(!isdigit(string[i])) return 0;
    }
    return 1;
}

int is_correct_word(char* string)
{
    size_t string_length = strlen(string);
    for(int i = 0; i < string_length; i++)
    {
        if(!isalpha(string[i])) return 0;
    }
    return 1;
}

int read_from_file(FILE* source, struct Employee** employees, size_t* size)
{
    struct Employee read;
    unsigned char* line[4];
    int length;

    *employees = (struct Employee*)malloc(sizeof(struct Employee)*1);
    int capacity = 1;
    *size = 0;

    while(!feof(source))
    {
        for(int i = 0; i < 4; i++)
        {
            int flag = get_string(source, &line[i], &length);
            switch(flag)
            {
                case eof_reached:
                case newline_reached:
                {
                    if(i != 3)
                    {
                        for(int j = 0; j < i; j++) free(line[j]);
                        return invalid_file_content;
                    }
                    break;
                }
                case space_reached:
                {
                    if(i == 3)
                    {
                        for(int j = 0; j < i; j++) free(line[j]);
                        return invalid_file_content;
                    }
                    break;
                }
                case memory_error:
                {
                    for(int j = 0; j < i; j++) free(line[j]);
                    return memory_error;
                }
            }
        }
        char* p;
        double wage = strtod(line[3], &p);
        if(*p != 0 || wage < 0 || !is_number(line[0]) || !is_correct_word(line[1]) || !is_correct_word(line[2]))
        {
            for(int i = 0; i < 4; i++) free(line[i]);
            return invalid_file_content;
        }
        (*size)++;
        if(*size == capacity)
        {
            capacity *= 2;
            struct Employee* for_realloc = (struct Employee*)realloc(*employees, sizeof(struct Employee)*capacity);
            if(for_realloc == NULL)
            {
                free(*employees);
                return memory_error;
            }
            *employees = for_realloc;
        }
        read.id = atoi(line[0]);
        read.first_name = strdup(line[1]);
        read.last_name = strdup(line[2]);
        read.wage = wage;
        (*employees)[(*size)-1] = read;
    }
    free(line[0]);
    free(line[1]);
    free(line[2]);
    free(line[3]);

    return success;
}

int64_t to_int64(double x)
{
    int64_t a;
    memcpy(&a, &x, 8);
    uint64_t mask = (uint64_t)(a >> 63) >> 1;
    return a ^ mask;
}

int cmp_double(double x1, double x2)
{
    int64_t a = to_int64(x1);
    int64_t b = to_int64(x2);
    if(a == b) return 0;
    return (a > b) ? 1 : -1;
}

int a_compare(const void* employee_1, const void* employee_2)
{
    struct Employee empl1 = *(struct Employee*)employee_1;
    struct Employee empl2 = *(struct Employee*)employee_2;
    int cmp = cmp_double(empl1.wage, empl2.wage);
    if (cmp) return cmp;
    cmp = strcmp(empl1.last_name, empl2.last_name);
    if (cmp) return cmp;
    cmp = strcmp(empl1.first_name, empl2.first_name);
    if (cmp) return cmp;
    if(empl1.id == empl2.id) return 0;
    return (empl1.id > empl2.id) ? 1 : -1;
}

int d_compare(const void* employee_1, const void* employee_2)
{
    struct Employee empl1 = *(struct Employee*)employee_1;
    struct Employee empl2 = *(struct Employee*)employee_2;
    int cmp = cmp_double(empl2.wage, empl1.wage);
    if (cmp) return cmp;
    cmp = strcmp(empl2.last_name, empl1.last_name);
    if (cmp) return cmp;
    cmp = strcmp(empl2.first_name, empl1.first_name);
    if (cmp) return cmp;
    if(empl1.id == empl2.id) return 0;
    return (empl2.id > empl1.id) ? 1 : -1;
}

int write_to_file(const struct Employee* employee, FILE* dest)
{
    return fprintf(dest, "%d %s %s %lf\n", employee->id, employee->first_name, employee->last_name, employee->wage);
}