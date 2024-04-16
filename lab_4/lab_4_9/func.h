#ifndef lad4 
#define lab4
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<time.h>
enum heap_data_types{
    BinaryHeap,
    BinomialHeap,
    FibonacciHeap,
    SkewHeap,
    LeftistHeap,
    Treap,
    HashSet,
    DynamicArray,
    BinarySearchTree,
    Trie,
    None,
};
typedef struct{
    char* heap_type;
    char* data_type;
    unsigned int* operators_quantity;
    time_t start_date_time;
    time_t end_date_time;
    unsigned int  min_processing_time;
    unsigned int max_processing_time;
    unsigned int departments_quantity;
    double overload_coefficient;
}departments_option;

typedef struct{
    time_t date_time;
    unsigned int priority;
    char* application_text;
} binary_heap_node;
typedef struct{
    int size;
    int current_size;
    binary_heap_node* heap;
} binary_heap;

typedef struct bin_node{
    unsigned int priority;
    size_t date_time;
    unsigned int rank;
    struct bin_node* next;
    struct bin_node* previous;
    struct bin_node* sons; // pointer to the last son;
    char* application_text;
} binomial_node;
typedef struct{
    binomial_node* max;
    binomial_node* last_node;
} binomial_heap;

typedef struct fib_node{
    unsigned int priority;
    time_t date_time;
    unsigned int rank;
    char* application_text;
    struct fib_node* previous;
    struct fib_node* next;
    struct fib_node* sons;
}fibonacci_node;
typedef struct {
    fibonacci_node* max;
    fibonacci_node* last_node;

}fibonacci_heap;
//enum data_types data_type_recognition(departments* dep);
int create_departments_option(departments_option** dep,FILE* file);


typedef struct left_node{
    unsigned int priority;
    time_t date_time;
    char* application_text;
    long int npl;   // value of quantity of nodes until end_node where npl is -1
    struct left_node* left;
    struct left_node* right;
}leftist_node;

typedef struct {
    leftist_node* root;
} leftist_heap;

typedef struct s_node{
    unsigned int priority;
    time_t date_time;
    char* application_text;
    struct s_node* left;
    struct s_node* right;
}skew_node;

typedef struct{
     skew_node* root;
}skew_heap;


binomial_heap* create_binomial_heap();
void add_elem_to_binomial_heap(binomial_heap* binom_heap,unsigned int priority,time_t date_time,char* application_text);
void remove_elem_from_binomial_heap(binomial_heap* binom_heap,binomial_node* node);
void delete_binomial_heap(binomial_heap* binom_heap);



binary_heap* create_binary_heap(int size);
unsigned int take_max_out_of_binary_heap(binary_heap* b_heap);
binary_heap_node* get_max_binary_heap(binary_heap* b_heap);
int check_files(int argc, char** argv);
int add_elem_to_binary_heap(unsigned int priority,time_t date_time,char* application_text,binary_heap* b_heap);
void siftUp(binary_heap* b_heap,int index);
int str_to_unsigned_int(char* str, unsigned int* num);
void merge_binary_heaps(binary_heap* heap1, binary_heap* heap2);
void delete_binary_heap(binary_heap** heap);
//int create_departmens(departments_option* dep);
void print_b_heap(binary_heap* b_heap){
    int i = 0;
    for(int i = 0; i <= b_heap->current_size; i++){
        printf("%u %u   \n",b_heap->heap[i].priority,b_heap->heap[i].date_time);
    }
    printf("\n\n");
}

fibonacci_heap* create_fibonacci_heap();
void delete_fibonacci_heap(fibonacci_heap* heap);
void merge_fibonacci_heaps(fibonacci_heap* heap1, fibonacci_heap* heap2);
void add_elem_to_fibonacci_heap(unsigned int priority, time_t date_time, char* application_text, fibonacci_heap* heap);
void remove_elem_from_fibonacci_heap(fibonacci_node* node,fibonacci_heap* heap);
#endif



leftist_heap* create_leftist_heap();
leftist_node* merge_leftist_heaps(leftist_node** node1, leftist_node** node2);
void add_elem_to_leftist_heap(unsigned int priority, time_t date_time,char* application_text,leftist_heap* heap);
void take_out_leftist_max(leftist_heap* heap);
void delete_leftist_heap(leftist_heap** heap);


skew_heap* create_skew_heap();
void add_elem_to_skew_heap(unsigned int priority,time_t date_time,char* application_text,skew_heap* heap);
void delete_skew_heap(skew_heap** heap);