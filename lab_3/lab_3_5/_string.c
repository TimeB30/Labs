
#include "_string.h"

struct String* create_String(const char* string)
{
    char* copy = string;
    int length = 0;
    for(; *copy != '\0'; ++length && (*copy++));
    struct String* s = (struct String*)malloc(sizeof(struct String));
    if(s == NULL) return NULL;
    s->length = length;
    s->string = (char*)malloc(sizeof(char)*(length+1));
    if(s->string == NULL)
    {
        free(s);
        return NULL;
    }
    for(int i = 0; i < length; i++)
    {
        s->string[i] = string[i];
    }
    s->string[length] = '\0';
    return s;
}

int clear_string(struct String* s)
{
    if(s->string != NULL) free((void*)s->string);
    s->string = (char*)malloc(sizeof(char)*1);
    if(s->string == NULL) return memory_error;
    s->string[0] = '\0';
    s->length = 0;
    return success;
}

int compare_strings(struct String* s1, struct String* s2)
{//returns positive if s1 > s2
    if(s1->length > s2->length) return bigger;
    if(s1->length < s2->length) return lesser;
    for(int i = 0; i < s1->length; i++)
    {
        if(s1->string[i] - s2->string[i] > 0) return bigger;
        if(s1->string[i] - s2->string[i] < 0) return lesser;
    }
    return equal;
}

int are_equal(struct String* s1, struct String* s2)
{
    if(s1->length != s2->length) return 0;
    for(int i = 0; i < s1->length; i++)
    {
        if(s1->string[i] != s2->string[i]) return 0;
    }
    return 1;
}

int copy(struct String* from, struct String** to)
{
    clear_string(*to);
    *to = create_String(from->string);
    if (*to == NULL) return memory_error;
    return success;
}

struct String* copy_to_new(struct String* string)
{
    struct String* new = create_String(string->string);
    return new;
}

int concat_strings(struct String* to, struct String* from)
{
    if(from->length == 0) return success;
    if(to->length == 0)
    {
        to = from;
        return success;
    }
    char* for_realloc = (char*)realloc(to->string, to->length + from->length);
    if(for_realloc == NULL)
    {
        clear_string(to);
        return memory_error;
    }
    to->string = for_realloc;
    for(int i = 0; i < from->length + 1; i++)
    {
        to->string[i+to->length] = from->string[i];
    }
    to->length += from->length;
    return success;
}

void delete_string(struct String* string)
{
    if(string->string != NULL) free(string->string);
    string->length = 0;
}