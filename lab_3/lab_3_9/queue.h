#ifndef LAB_3_9_QUEUE_H
#define LAB_3_9_QUEUE_H

#include "tree.h"
#include <stdbool.h>

struct Q
{
    struct Node** data; // array of pointers to nodes
    int low_border;
    int high_border;
    int count;
    int capacity;
};

struct Q* init(int size);
void push(struct Q* q, struct Node* element);
struct Node* pop(struct Q* q);
void delete_q(struct Q* q);
bool is_empty(struct Q* q);

#endif //LAB_3_9_QUEUE_H
