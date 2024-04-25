#ifndef lad4 
#define lab4
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<ctype.h>
typedef struct {
    void* (*create_heap)();
    void (*add_elem_to_heap)(unsigned int,time_t,unsigned int,char*,void*);
    unsigned int (*get_max_appln_id)(void*);
    void (*remove_max)(void*);
    void (*delete_heap)(void*);
}heap_context;

typedef struct {
    void* strct;
    void (*insert)(unsigned int,unsigned int, void*, void*);
    void** (*get_struct_data)(unsigned int, void*);
    void (*delete_struct)(void*, void (*) (void*));
}struct_to_save_heaps_context;
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
typedef struct {
    departments_option* options;
    unsigned int* departments_numbers;
    time_t current_time;
    heap_context* heap_context;
    struct_to_save_heaps_context* struct_context;
    FILE* log_file;
}departments;

typedef struct{
    time_t date_time;
    unsigned int priority;
    char* application_text;
    unsigned int dep_number;
    unsigned int application_id;
} binary_heap_node;
typedef struct{
    int size;
    int current_size;
    binary_heap_node* heap;
} binary_heap;

typedef struct bin_node{
    unsigned int priority;
    time_t date_time;
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
    void** data;
}hash_table_node;

typedef struct {
    unsigned int size;
    unsigned int current_size;
    unsigned int dep_quantity;
    hash_table_node* array;
}hash_table;
typedef struct{
    void** data;
}dynamic_array_node;
typedef struct{
    unsigned int size;
    unsigned int current_size;
    dynamic_array_node* array;
}dynamic_array;

typedef struct bst_n{
    void** data;
    struct bst_n* left;
    struct bst_n* right;
}bst_node;
typedef struct{
    bst_node** root;
}bst;
typedef struct tri_node{
    void** data;
    struct tri_node** array;
}trie_node;
typedef struct{
    trie_node* root;
}trie;

typedef struct{
    time_t date_time;
    unsigned int priority;
    unsigned int dep_num;
    char* appln_text;
    unsigned int text_size;
    unsigned int appln_id;
}application;

typedef struct{
    time_t end_date_time;
    unsigned int appln_id;
    char operator_name[10];
}application_lite;
binomial_heap* create_binomial_heap();
void* create_binomial_heap_interface();
void add_elem_to_binomial_heap(unsigned int priority,time_t date_time, unsigned int appln_id,char* application_text,binomial_heap* binom_heap);
void add_elem_to_binomial_heap_interface(unsigned int priority,time_t date_time, unsigned int appln_id,char* application_text,void* binom_heap);
void merge_binomial_heaps(binomial_heap* heap1, binomial_heap* heap2);
void merge_binomial_heaps_interface(void* heap1, void* heap2);
unsigned int get_binomial_max_appln_id(binomial_heap* heap);
unsigned int get_binomial_max_appln_id_interface(void* heap);
void remove_binomial_heap_max(binomial_heap* heap);
void remove_binomial_heap_max_interface(void* heap);
void delete_binomial_heap(binomial_heap* binom_heap);
void delete_binomial_heap_interface(void* heap);



binary_heap* create_binary_heap();
void* create_binary_heap_interface();
void add_elem_to_binary_heap_interface(unsigned int priority, time_t date_time,unsigned int appln_id, char* application_text, void* b_heap);
void add_elem_to_binary_heap(unsigned int priority,time_t date_time, unsigned int appln_id,char* application_text,binary_heap* b_heap);
void merge_binary_heaps(binary_heap* heap1, binary_heap* heap2);
void merge_binary_heaps_interface(void* heap1, void* heap2);
unsigned int get_binary_max_appln_id(binary_heap* heap);
unsigned int get_binary_max_appln_id_interface(void* heap);
void remove_binary_max(binary_heap* b_heap);
void remove_binary_max_interface(void* b_heap);
void delete_binary_heap(binary_heap* heap);
void delete_binary_heap_interface(void* heap);


fibonacci_heap* create_fibonacci_heap();
void* create_fibonacci_heap_interface();
void add_elem_to_fibonacci_heap(unsigned int priority, time_t date_time, unsigned int appln_id ,char* application_text, fibonacci_heap* heap);
void add_elem_to_fibonacci_heap_interface(unsigned int priority, time_t date_time, unsigned int appln_id ,char* application_text, void* heap);
void merge_fibonacci_heaps(fibonacci_heap* heap1, fibonacci_heap* heap2);
unsigned int get_fibonacci_max_appln_id(fibonacci_heap* heap);
unsigned int get_fibonacci_max_appln_id_interface(void* heap);
void remove_fibonacci_max(fibonacci_heap* heap);
void remove_fibonacci_max_interface(void* heap);
void delete_fibonacci_heap(fibonacci_heap* heap);
void delete_fibonacci_heap_interface(void* heap);




leftist_heap* create_leftist_heap();
void* create_leftist_heap_interface();
void add_elem_to_leftist_heap(unsigned int priority, time_t date_time, unsigned int appln_id,char* application_text,leftist_heap* heap);
void add_elem_to_leftist_heap_interface(unsigned int priority, time_t date_time, unsigned int appln_id,char* application_text,void* heap);
void merge_leftist_heaps(leftist_heap* heap1, leftist_heap* heap2);
unsigned int get_leftist_max_appln_id(leftist_heap* heap);
unsigned int get_leftist_max_appln_id_interface(void* heap);
void remove_leftist_max(leftist_heap* heap);
void remove_leftist_max_interface(void* heap);
void delete_leftist_heap(leftist_heap* heap);
void delete_leftist_heap_interface(void* heap);


skew_heap* create_skew_heap();
void* create_skew_heap_interface();
void add_elem_to_skew_heap(unsigned int priority,time_t date_time, unsigned int appln_id, char* application_text,skew_heap* heap);
void add_elem_to_skew_heap_interface(unsigned int priority,time_t date_time, unsigned int appln_id, char* application_text,void* heap);
unsigned int get_skew_max_appln_id(skew_heap* heap);
unsigned int  get_skew_max_appln_id_interface(void* heap);
void merge_skew_heaps(skew_heap* heap1, skew_heap* heap2);
void remove_skew_max(skew_heap* heap);
void remove_skew_max_interface(void* heap);
void delete_skew_heap(skew_heap* heap);
void delete_skew_heap_interface(void* heap);


treap_heap* create_treap_heap();
void* create_treap_heap_interface();
void add_elem_to_treap_heap(unsigned int priority, time_t date_time,unsigned int appln_id, char* application_text, treap_heap* heap);
void add_elem_to_treap_heap_interface(unsigned int priority, time_t date_time,unsigned int appln_id, char* application_text, void* heap);
void merge_treap_heaps(treap_heap* heap1, treap_heap* heap2);   // any node1 date_time should be less than any node2 date_time
unsigned int get_treap_max_appln_id(treap_heap* heap);
unsigned int get_treap_max_appln_id_interface(void* heap);
void remove_treap_max(treap_heap* heap); //splitting should be done with date_time comparison
void remove_treap_max_interface(void* heap);
void delete_treap_heap(treap_heap* heap);
void delete_treap_heap_interface(void* heap);

int check_files(int argc, char** argv);
int str_to_int(char* str, int* num);
void generate(FILE* file);

departments* create_departments(departments_option* dep_ops);
void start_work(departments* deps,int argc,char** argv);
void close_department(departments* deps);

hash_table* create_hash_table();
void** get_from_hash_table(unsigned int key,hash_table* table);
void** get_from_hash_table_interface(unsigned int key,void* table);
void insert_into_hash_table(unsigned int key,unsigned int dep_capacity, void* ptr,hash_table* table);
void insert_into_hash_table_interface(unsigned int key,unsigned int dep_capacity, void* ptr,void* table);
void delete_hash_table(hash_table* table,void (*deleter)(void*));
void delete_hash_table_interface(void* table,void (*deleter)(void*));

dynamic_array* create_dynamic_array();
void insert_into_dynamic_array(unsigned int dep_num,unsigned int capacity,void* ptr,dynamic_array* array);
void insert_into_dynamic_array_interface(unsigned int dep_num,unsigned int capacity,void* ptr,void* array);
void** get_from_dynamic_array(unsigned int dep_num,dynamic_array* array);
void** get_from_dynamic_array_interface(unsigned int dep_num,void* array);
void delete_dynamic_array(dynamic_array* array,void (*deleter)(void*));
void delete_dynamic_array_interface(void* array,void (*deleter)(void*));

bst*  create_binary_tree();
void insert_into_binary_tree(unsigned int dep_num,unsigned int capacity,void* ptr,bst* tree);
void insert_into_binary_tree_interface(unsigned int dep_num,unsigned int capacity,void* ptr,void* tree);
void** get_from_binary_tree(unsigned int dep_num,bst* tree);
void** get_from_binary_tree_interface(unsigned int dep_num, void* tree);
void delete_binary_tree_inside(bst_node* root,void (*deleter)(void*));
void delete_binary_tree(bst* tree,void (*deleter)(void*));
void delete_binary_tree_interface(void* tree, void (*deleter)(void*));

trie* create_trie();
void insert_into_trie(unsigned int dep_num,unsigned int capacity,void* ptr,trie* tree);
void insert_into_trie_interface(unsigned int dep_num, unsigned int capacity,void* ptr,void* tree);
void** get_from_trie(unsigned int dep_num,trie* tree);
void** get_from_trie_interface(unsigned int dep_num, void* tree);
void delete_trie(trie* tree, void (*deleter)(void*));
void delete_trie_interface(void* tree, void (*deleter)(void*));
#endif