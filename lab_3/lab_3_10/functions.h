#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum exit_codes
{
    memory_error,
    success,
};

struct Node
{
    char value;
    struct Node* parent;
    struct Node* child;
    struct Node* elder_brother;
};

struct Node* create_node();
int read_line(FILE* stream, struct Node* root);
void print_tree(FILE* stream, struct Node* root, int tab);
void free_tree(struct Node* root);
int read_from_file(FILE* in, FILE* out);
void print_expression(FILE* stream, struct Node* root);