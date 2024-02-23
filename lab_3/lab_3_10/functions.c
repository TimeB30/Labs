#include "functions.h"

struct Node* create_node()
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node) * 1);
    if(node == NULL) return NULL;
    node->child = NULL;
    node->elder_brother = NULL;
    return node;
}

int read_line(FILE* stream, struct Node* root)
{
    struct Node* node = root;
    char c = 'x';

    while(c != '\n' && c != EOF)
    {// "(...)" considered inappropriate whilst "A(B, C(D))" is considered appropriate :)
        c = fgetc(stream);
        if(isalpha(c)) node->value = c;
        else if(c == '(')
        {
            node->child = create_node();
            if(node->child == NULL) return memory_error;
            node->child->parent = node;
            node = node->child;
        }
        else if(c == ')')
        {
            node = node->parent;
        }
        else if(c == ',')
        {
            node->elder_brother = create_node();
            if(node->elder_brother == NULL) return memory_error;
            node->elder_brother->parent = node->parent;
            node = node->elder_brother;
        }
    }
    return success;
}

void free_tree(struct Node* root)
{
    if(root == NULL) return;
    free_tree(root->elder_brother);
    free_tree(root->child);
    free(root);
}

void print_tree(FILE* stream, struct Node* root, int tab)
{
    if(root == NULL) return;
    for(int i = 0; i < tab; i++) fprintf(stream, "\t");
    fprintf(stream, "%c\n", root->value);
    print_tree(stream, root->child, tab + 1);
    print_tree(stream, root->elder_brother, tab);
}

void print_expression(FILE* stream, struct Node* root)
{
    if(root == NULL) return;
    fprintf(stream, "%c", root->value);
    if(root->child != NULL) {fprintf(stream, " ("); print_expression(stream, root->child); fprintf(stream, ")"); }
    if(root->elder_brother != NULL) { fprintf(stream, ", "); print_expression(stream, root->elder_brother); }

}

int read_from_file(FILE* in, FILE* out)
{
    while(!feof(in))
    {
        struct Node* root = create_node();
        root->parent = NULL;
        int exit = read_line(in, root);
        if(exit == memory_error)
        {
            free_tree(root);
            return memory_error;
        }
        fprintf(out, "Expression:\n");
        print_expression(out, root);
        fprintf(out, "\nTree:\n");
        print_tree(out, root, 0);
        free_tree(root);
    }
    return success;
}