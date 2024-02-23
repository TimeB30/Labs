#include "queue.h"


struct Q* init(int size)
{
    int size_total = (int)pow(2, size);
    struct Q* q = (struct Q*)calloc(1, sizeof(struct Q));
    if(q == NULL) return NULL;
    q->data = (struct Node**)calloc(size_total, sizeof(struct Node*));
    if(q->data == NULL) {free(q); return NULL; }
    q->capacity = size_total;
    q->low_border = q->high_border = size_total - 1;
    return q;
}

void push(struct Q* q, struct Node* element)
{
    if(q->count == q->capacity) return;
    q->data[q->low_border--] = element;
    q->count++;
    if(q->low_border < 0) q->low_border = q->capacity - 1;
}

struct Node* pop(struct Q* q)
{
    if(is_empty(q)) return NULL;
    struct Node* element = q->data[q->high_border--];
    q->count--;
    if(q->high_border < 0) q->high_border = q->capacity - 1;
    return element;
}

void delete_q(struct Q* q)
{
    free(q->data);
    free(q);
}

bool is_empty(struct Q* q)
{
    return (q->count == 0);
}