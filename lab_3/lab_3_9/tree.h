

#ifndef LAB_3_9_TREE_H
#define LAB_3_9_TREE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

enum exit_codes
{
    memory_error,
    success,
};

struct Node
{
    char* word; //key
    size_t amount;
    int height;
    struct Node* left;
    struct Node* right;
};

int insert(struct Node* node, char* word, int amount);
const struct Node* get_min(const struct Node* node);
const struct Node* get_max(const struct Node* node);
struct Node* delete(struct Node* head, char* keyword);
int get_height(const struct Node* node);
void update_height(struct Node* node);
int get_balance(const struct Node* node);
void swap_nodes(struct Node* a, struct Node* b);
void right_rotate(struct Node* node);
void left_rotate(struct Node* node);
void balance(struct Node* node);
int find_word(struct Node* node, const char* word);
void find_shortest(const struct Node* head, char** word, int max);
void find_longest(const struct Node* head, char** word, int min);
void find_n_most_often(struct Node* head, int** amounts, char*** words, int amount);
void delete_tree(struct Node* tree);

void print_tree(const struct Node *q, long n);

#endif //LAB_3_9_TREE_H
