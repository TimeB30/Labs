
#include "tree.h"
#include "functions.h"
#include "queue.h"

int get_string(FILE* stream, char** string, int* length, const char* separators)
{
    *length = 0;
    int capacity = 1;
    char* for_realloc;
    int c = fgetc(stream);
    *string = (char*)malloc(sizeof(char)*1);
    if(*string == NULL) return memory_error;
    size_t sep_amount = strlen(separators);
    while(c != EOF)
    {
        for(int i = 0; i < sep_amount; i++) if(c == separators[i])
        {
            (*string)[*length] = '\0';
            if(c == ' ') return space_reached;
            if (c == EOF) return eof_reached;
            if (c == '\n') return newline_reached;
            if (c == '\0') return endl_reached;
            return success;
        }
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

    return success;
}

int read_from_file(FILE* stream, struct Node* head, char* separators)
{
    while(!feof(stream))
    {
        char* string;
        int length;
        if(get_string(stream, &string, &length, separators) == memory_error) return memory_error;
        if(length != 0)
        {
            if (insert(head, string, 0) == memory_error)
            {
                delete_tree(head);
                free(string);
                return memory_error;
            }
        }
        //free(string);
    }

    return success;
}

int get_cmd_code(const char* command)
{
    if(!strcmp(command, "find")) return find;
    if(!strcmp(command, "common")) return common;
    if(!strcmp(command, "shortest")) return shortest;
    if(!strcmp(command, "longest")) return longest;
    if(!strcmp(command, "print")) return print;
    if(!strcmp(command, "quit")) return quit;
    if(!strcmp(command, "save")) return save;
    if(!strcmp(command, "load")) return load;
    if(!strcmp(command, "height")) return height;
    return unknown;
}

int is_number(const char* string)
{
    size_t string_length = strlen(string);
    for(int i = 0; i < string_length; i++){
        if(!isdigit(string[i])) return 0;
    }
    return 1;
}

int save_to(FILE* dest, struct Node* tree)
{
    if(tree && tree->word)
    {

        struct Q* q;
        q = init(tree->height);
        if(q == NULL) return memory_error;
        push(q, tree);
        while(!is_empty(q))
        {
            struct Node* tmp = pop(q);
            if(tmp == NULL) return memory_error;
            if(fprintf(dest, "%lld+%s+", tmp->amount, tmp->word) < 0) return memory_error;
            if(tmp->left != NULL) push(q, tmp->left);
            if(tmp->right != NULL) push(q, tmp->right);
        }
        delete_q(q);
    }
    return success;

}

int load_from(FILE* origin, struct Node* _tree)
{
    while(!feof(origin))
    {
        struct Node tree;
        int len = 0;
        char* amount;
        if(get_string(origin, &amount, &len, "+") == memory_error)
        {
            free(amount);
            free(tree.word);
            return memory_error;
        }
        if(get_string(origin, &tree.word, &len, "+") == memory_error)
        {
            free(amount);
            free(tree.word);
            return memory_error;
        }
        if(insert(_tree, tree.word, atoi(amount)) == memory_error)
        {
            free(amount);
            free(tree.word);
            delete_tree(_tree);
            return memory_error; }
        free(amount);
        free(tree.word);
    }
    return success;
}