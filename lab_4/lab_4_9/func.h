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
    unsigned int max_priority;
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
    unsigned int dep_number;
    unsigned int application_id
} binary_heap_node;
typedef struct{
    unsigned int size;
    unsigned int current_size;
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
    unsigned int application_id;
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
    unsigned int application_id;
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
    unsigned int application_id;
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
    unsigned int application_id;
}skew_node;

typedef struct{
     skew_node* root;
}skew_heap;

typedef struct tr_node{
    unsigned int priority;  // key insert(key) split(key)
    time_t date_time;
    char* application_text;
    struct tr_node* left;
    struct tr_node* right;
    unsigned int application_id;
}treap_node;
typedef struct{
    treap_node* root;
}treap_heap;



typedef struct hash_node{
    struct hash_node* next;
    void* ptr;
    unsigned int department_number;
}hash_table_node;

typedef struct {
    unsigned int size;
    unsigned int current_size;
    unsigned int dep_quantity;
    hash_table_node* array;
}hash_table;

typedef struct {
    void* (*create_heap)();
    void (*add_elem_to_heap)(unsigned int,time_t,unsigned int,char*,void*);
}heap_context;

typedef struct {
    void* strct;
    void (*insert)(unsigned int, void*, void**); // можно сделать структуры которые хранят void потому что операции вставки и удаление сами приведут тип  void  к которому нужно - подумать
    // сделать функцию find которая возвращает указатель на void* - куча  а потом уже это указатель в зависимоти от типа кучи будет сам преобразовываться в нужный тип
    void* (*get_heap)(unsigned int, void*);
}struct_to_save_heaps_context;
typedef struct {
    departments_option* options;
    unsigned int* departments_capacity;
    time_t current_time;
    long int time_we_have;  // time_to_work   start - end time
    heap_context* heap_context;
    struct_to_save_heaps_context* struct_context;
    unsigned int* applications_quantity;
    unsigned int* departments_number;
    fibonacci_heap* all_applications;
}departments;

typedef struct{
    time_t date_time;
    unsigned int priority;
    int department_number;
    char* application_text;
}application;


binomial_heap* create_binomial_heap();
void add_elem_to_binomial_heap(unsigned int priority,time_t date_time, unsigned int appln_id,char* application_text,binomial_heap* binom_heap);
void add_elem_to_binomial_heap_interface(unsigned int priority,time_t date_time, unsigned int appln_id,char* application_text,void* binom_heap);
void merge_binomial_heaps(binomial_heap* heap1, binomial_heap* heap2);
void merge_binomial_heaps_interfae(void* heap1, void* heap2);
void remove_binomial_heap_max(binomial_heap* heap);
void delete_binomial_heap(binomial_heap* binom_heap);



binary_heap* create_binary_heap();
void* create_binary_heap_interface();
void add_elem_to_binary_heap_interface(unsigned int priority, time_t date_time,unsigned int appln_id, char* application_text, void* b_heap);
void add_elem_to_binary_heap(unsigned int priority,time_t date_time, unsigned int appln_id,char* application_text,binary_heap* b_heap);
void merge_binary_heaps(binary_heap* heap1, binary_heap* heap2);
void merge_binary_heaps_interface(void* heap1, void* heap2);
void* get_binary_max(binary_heap* heap);
void remove_binary_max(binary_heap* b_heap);
void delete_binary_heap(binary_heap** heap);
unsigned int get_application_id_binary_node(binary_heap_node* node);
//binary_heap_node* get_max_binary_heap(binary_heap* b_heap);


fibonacci_heap* create_fibonacci_heap();
void add_elem_to_fibonacci_heap(unsigned int priority, time_t date_time, unsigned int appln_id ,char* application_text, fibonacci_heap* heap);
void merge_fibonacci_heaps(fibonacci_heap* heap1, fibonacci_heap* heap2);
fibonacci_node* get_fibonacci_max(fibonacci_heap* heap);
void remove_fibonacci_max(fibonacci_heap* heap);
void delete_fibonacci_heap(fibonacci_heap* heap);
#endif



leftist_heap* create_leftist_heap();
void add_elem_to_leftist_heap(unsigned int priority, time_t date_time, unsigned int appln_id,char* application_text,leftist_heap* heap);
void merge_leftist_heaps(leftist_heap* heap1, leftist_heap* heap2);
void remove_leftist_max(leftist_heap* heap);
void delete_leftist_heap(leftist_heap** heap);


skew_heap* create_skew_heap();
void add_elem_to_skew_heap(unsigned int priority,time_t date_time, unsigned int appln_id, char* application_text,skew_heap* heap);
void merge_skew_heaps(skew_heap* heap1, skew_heap* heap2);
void remove_skew_max(skew_heap* heap);
void delete_skew_heap(skew_heap** heap);


treap_heap* create_treap_heap();
void add_elem_to_treap_heap(unsigned int priority, time_t date_time,unsigned int appln_id, char* application_text, treap_heap* heap);
void merge_treap_heaps(treap_heap* heap1, treap_heap* heap2);   // any node1 date_time should be less than any node2 date_time
void remove_treap_max(treap_heap* heap); //splitting should be done with date_time comparison
void delete_treap_heap(treap_heap* heap);

int check_files(int argc, char** argv);
int str_to_unsigned_int(char* str, unsigned int* num);


departments* create_departments(departments_option* dep_ops);
void add_applications_to_departments(departments* dep,char** file_with_applications,int file_count);

hash_table* create_hash_table();
void* get_from_hash_table(unsigned int key,hash_table* table);
void* get_from_hash_table_interface(unsigned int key,void* table);
void insert_into_hash_table(unsigned int key, void* ptr,hash_table** table);
void insert_into_hash_table_interface(unsigned int key, void* ptr,void** table);
//unsigned int get_capacity_hash_node(hash_table_node* node);
//unsigned int get_application_count(hash_table_node* node);
int check_overload_status_hash_node(hash_table_node* node);
void delete_hash_table(hash_table* table);