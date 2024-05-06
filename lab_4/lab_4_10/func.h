#ifndef lab4_10
#define  lab4_10
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<ctype.h>
#define uint_max 4294967295
enum options{
    prefix,
    postfix,
    infix,
    left_value,
    right_value,
    error,
    change_add,
    change_mult,
    change_sub,
    change_pow,
    change_div,
    change_rem,
    change_xor,
    change_and,
    change_or,
    change_init,
    change_inverse,
    change_input,
    change_output,
    in_use,
};
enum run_errors{
    name_error,
    good_name,
    success,
    init,
    run_error,
    empty,
    too_many_arguments,
};
typedef struct{
    unsigned int size;
    unsigned int current_size;
    char* string;
}string;
typedef struct{
    string* realname;
    string* name;
    int is_binary;
    int priority;
//    unsigned int  (*func)(unsigned int, unsigned int,int*);
    void* func;
}operation;
typedef struct{
    int operations_count;
    operation* ops;
}operations;
typedef struct{
    string** str;
}compile_options;
typedef struct tr_nod
{
    struct tr_nod** trie_nodes;
    unsigned int value;
    char letter;
}trie_node;
typedef struct
{
    trie_node** root;
}trie;

trie* create_trie();
void add_value_to_trie(string* variable_name, unsigned int value,trie* tr,int* status);
unsigned int get_value_from_trie(string* variable_name,trie* tr,int* status);


void add_to_string(string* str,char letter);
string* create_string(int* status);
unsigned int strtouint(char* str,unsigned int base,int* status);
operations* create_operations(int* status);
compile_options* create_compile_options(int* status);
void apply_settings(operations* ops,compile_options* comp_ops,FILE* file,int* status,string* error_message);
void run(operations* ops,compile_options* comp_ops,FILE* run_file, int debug_status,string* error_message,trie* variables_data,unsigned int base_assign, unsigned int base_input,unsigned int base_output);

void inverse(unsigned int* num);
unsigned int input_inside(unsigned int base_input,int* status);
unsigned int input(void* base_input, void* not_used,void* status);
unsigned int output(void* num, void* base, void* not_used);
unsigned int  output_inside(unsigned int num,unsigned int base);
void get_settings(FILE* file,unsigned int base_assign, unsigned int base_input, unsigned int base_output);


unsigned int add(unsigned int num1, unsigned int num2,int* status);
unsigned int mult(unsigned int num1, unsigned int num2,int* status);
unsigned int sub(unsigned int num1, unsigned int num2, int* status);
unsigned int mod_pow(unsigned int base, unsigned int exp, int* status);
unsigned int my_div(unsigned int num1, unsigned int num2, int* status);
unsigned int rem(unsigned int num1, unsigned int num2, int* status);
unsigned int xor(unsigned int num1, unsigned int num2, int* status);
unsigned int and(unsigned int num1, unsigned int num2, int* status);
unsigned int or(unsigned int num1, unsigned int num2,int* status);
unsigned int initialize(string* new_name, trie* tr,int* value);
unsigned int not(unsigned int num1, unsigned int num2,int* status);

//
//unsigned int add(void* num1, void* num2,void* status);
//unsigned int mult(void* num1, void* num2,void* status);
//unsigned int sub(void* num1, void* num2,void* status);
//unsigned int mod_pow(void* base, void* exp, void* status);
//unsigned int my_div(void* num1, void* num2,void* status);
//unsigned int rem(void* num1, void* num2,void* status);
//unsigned int xor(void* num1, void* num2,void* status);
//unsigned int and(void* num1, void* num2,void* status);
//unsigned int or(void* num1, void* num2,void* status);
//unsigned int initialize(void* name, void* tr,void* value);
//unsigned int not(void* num1, void* num2,void* status);
#endif