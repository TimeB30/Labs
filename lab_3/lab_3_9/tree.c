
#include "tree.h"

int insert(struct Node* node, char* word, int amount)
{
    if(!strlen(word)) return success;
    if(node->word == NULL)
    {
        node->word = strdup(word);
        if(node->word == NULL) {free(word); return memory_error; }
        free(word);
        if(amount != 0) node->amount = amount;
        else node->amount = 1;
        node->height = 0;
        node->right = NULL;
        node->left = NULL;
        return success;
    }
    int cmp = strcmp(word, node->word);
    if(cmp == 0) { node->amount++; return success; }
    if(cmp < 0)
    {
        if(node->left == NULL)
        {
            node->left = (struct Node*)malloc(sizeof(struct Node));
            if(node->left == NULL) { free(word); return memory_error; }
            node->left->word = strdup(word);
            if(node->left->word == NULL) { free(word); return memory_error; }
            free(word);
            if(amount != 0) node->left->amount = amount;
            else node->left->amount = 1;
            node->left->height = 0;
            node->left->right = NULL;
            node->left->left = NULL;
        }
        else if(insert(node->left, word, amount) == memory_error) return memory_error;
    }
    else
    {
        if(node->right == NULL)
        {
            node->right = (struct Node*)malloc(sizeof(struct Node));
            if(node->right == NULL) { free(word); return memory_error; }
            node->right->word = strdup(word);
            if(node->right->word == NULL) { free(word); return memory_error; }
            if(amount != 0) node->right->amount = amount;
            else node->right->amount = 1;
            node->right->height = 0;
            node->right->right = NULL;
            node->right->left = NULL;
        }
        else if(insert(node->right, word, amount) == memory_error) return memory_error;
    }
    update_height(node);
    if(amount == 0)
    {
    }
    balance(node);
    return success;
}

const struct Node* get_min(const struct Node* node)
{
    if(node == NULL) return NULL;
    if(node->left == NULL) return node;
    return get_min(node->left);
}

const struct Node* get_max(const struct Node* node)
{
    if(node == NULL) return NULL;
    if(node->right == NULL) return node;
    return get_max(node->right);
}

struct Node* delete(struct Node* head, char* keyword)
{
    if(head == NULL) return NULL;
    else if(strcmp(keyword,head->word) < 0) head->left = delete(head->left, keyword);
    else if(strcmp(keyword,head->word) > 0) head->right = delete(head->right, keyword);
    else
    {
        struct Node* copy = head;
        if(head->left == NULL || head->right == NULL) head = (head->left == NULL) ? head->right : head->left;
        else
        {
            const struct Node* max_in_left = get_max(head->left);
            head->word = max_in_left->word;
            head->amount = max_in_left->amount;
            head->left = delete(head->left, max_in_left->word);
        }
        free(copy->word);
        free(copy);
    }
    if(head != NULL)
    {
        update_height(head);
        balance(head);
    }
    return head;
}

int get_height(const struct Node* node)
{
    return (node == NULL) ? -1 : node->height;
}

void update_height(struct Node* node)
{
    node->height = 1 + (get_height(node->left) > get_height(node->right) ? get_height(node->left) : get_height(node->right));
}

int get_balance(const struct Node* node)
{
    return (node == NULL) ? 0 : get_height(node->right) - get_height(node->left);
}

void swap_nodes(struct Node* a, struct Node* b)
{
    char* word = a->word;
    a->word = b->word;
    b->word = word;
    size_t amount = a->amount;
    a->amount = b->amount;
    b->amount = amount;
}

void right_rotate(struct Node* node)
{
    swap_nodes(node, node->left);
    struct Node* buf = node->right;
    node->right = node->left;
    node->left = node->right->left;
    node->right->left = node->right->right;
    node->right->right = buf;
    update_height(node->right);
    update_height(node);
}

void left_rotate(struct Node* node)
{
    swap_nodes(node, node->right);
    struct Node* buf = node->left;
    node->left = node->right;
    node->right = node->left->right;
    node->left->right = node->left->left;
    node->left->left = buf;
    update_height(node->left);
    update_height(node);
}

void balance(struct Node* node)
{
    int balance = get_balance(node);
    if(balance == -2)
    {
        if(get_balance(node->left) == 1) left_rotate(node->left);
        right_rotate(node);
    }
    else if (balance == 2)
    {
        if(get_balance(node->right) == -1) right_rotate(node->right);
        left_rotate(node);
    }
}

int find_word(struct Node* node, const char* word)
{
    if(node->word == NULL) return 0;
    int cmp = strcmp(word, node->word);
    if(!cmp) return node->amount;
    if(cmp < 0) find_word(node->left, word);
    else find_word(node->right, word);
}

void find_shortest(const struct Node* head, char** word, int max)
{
    if(head->word == NULL || head == NULL) return;
    if(max > strlen(head->word)) { *word = head->word; max = strlen(head->word); }
    find_shortest(head->left, word, max);
    find_shortest(head->right, word, max);
}

void find_longest(const struct Node* head, char** word, int min)
{
    if(head->word == NULL || head == NULL) return;
    if(min < strlen(head->word)) { *word = head->word; min = strlen(head->word); }
    find_longest(head->left, word, min);
    find_longest(head->right, word, min);
}

void find_n_most_often(struct Node* head, int** amounts, char*** words, int amount)
{
    if(head->word == NULL || head == NULL) return;
    for(int i = 0; i < amount; i++)
    {
        if((*amounts)[i] < head->amount)
        {
            for(int j = amount - 1; j > i; j--) { (*amounts)[j] = (*amounts)[j-1]; (*words)[j] = (*words)[j-1]; }
            (*amounts)[i] = head->amount;
            (*words)[i] = head->word;
            break;
        }
    }

    find_n_most_often(head->left, amounts, words, amount);
    find_n_most_often(head->right, amounts, words, amount);
}


void print_tree(const struct Node *q, long n)
{
    long i;
    if (q && q->word)
    {
        print_tree(q->right, n+7);
        for (i = 0; i < n; i++) printf(" ");
        printf("%lld %s\n", q->amount, q->word);
        print_tree(q->left, n+7);
    }
}

void delete_tree(struct Node* tree)
{
    if(tree == NULL || tree->word == NULL || tree->left == NULL || tree->right == NULL) return;
    delete_tree(tree->left);
    delete_tree(tree->right);
    free(tree->word);
    free(tree->left);
    free(tree->right);
}