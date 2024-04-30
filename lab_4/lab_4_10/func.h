#ifndef lab4_10
#define  lab4_10
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
typedef struct
{
    unsigned int size;
    unsigned int current_size;
    char* string;
}string;
typedef struct tr_nod
{
    struct tr_nod** trie_nodes;
    unsigned int value;
    char letter;
}trie_node;
typedef struct
{
    trie_node** root;
}trie ;

trie* create_trie();
void add_value_to_trie(string* variable_name, unsigned int value,trie* tr,int* status);
unsigned int get_value_from_trie(string* variable_name,trie* tr,int* status);


void add_to_string(string* str,char letter);
string* create_string(int* status);
unsigned int strtouint(char* str,unsigned int base,int* status);
void inverse(unsigned int* num);
unsigned int input(unsigned int base_input,int* status);
void get_settings(FILE* file,unsigned int base_assign, unsigned int base_input, unsigned int base_output);
#endif