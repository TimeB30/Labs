#include"func.h"
void memory_error(){
    perror("Memory allocation error\n");
    exit(EXIT_FAILURE);
}

void create_trie_node_array(trie_node*** array){
    *array = (trie_node**)malloc(sizeof(trie_node*)*62);
    if (*array == NULL){
        memory_error();
    }
    (*array)[61] = (trie_node*)malloc(sizeof(trie_node));
    if ((*array)[61] == NULL){
        memory_error();
    }
    (*array)[61]->letter = '_';
    char current_char = 48;
    for (int i = 0; i < 61; i++){
        (*array)[i] = (trie_node*)malloc(sizeof(trie_node));
        if ((*array)[i] == NULL){
            memory_error();
        }
        if (i < 10){
            (*array)[i]->letter = (char)(current_char + i);
        }
        else if (i < 36) {
            current_char = 55;
            ((*array)[i])->letter = (char)(current_char + i);
        }
        else {
            current_char = 61;
            (*array)[i]->letter = (char)(current_char + i);
        }
    }
}


trie* create_trie()
{
    trie* tr = (trie*)malloc(sizeof(trie));
    if (tr == NULL)
    {
        memory_error();
    }
    create_trie_node_array(&tr->root);
    if (tr->root == NULL)
    {
        memory_error();
    }
    return tr;
}
void  add_value_to_trie_inside(const char* valuable_name, unsigned int value, trie_node** first_array,int* status){
    if ((valuable_name[0] > 47) && (valuable_name[0] < 58)){
        *status = 1;
    }
    unsigned int i = 0;
    unsigned int i2;
    unsigned int name_index = 0;
    trie_node** tmp = first_array;
    trie_node** tmp2;
    while (valuable_name[name_index] != '\0'){
        if (i == 61){
            *status = 1;
        }
        if (tmp[i]->letter == valuable_name[name_index]){
            name_index++;
            tmp2 = tmp;
            tmp = tmp[i]->trie_nodes;
            i2 = i;
            i = 0;
        }
        i++;
    }
    tmp2[i2]->value = value;
}

void add_value_to_trie(string* valuable_name, unsigned int value, trie* tr,int* status){
    add_value_to_trie_inside(valuable_name->string, value, tr->root,status);
}

unsigned int  get_value_from_trie_inside(const char* variable_name,trie_node** first_array,int* status){
    if ((variable_name[0] > 47) && (variable_name[0] < 58)){
        *status = 1;
        return 0;
    }
    unsigned int i = 0;
    unsigned int name_index = 0;
    trie_node** tmp = first_array;
    while(variable_name[name_index] != '\0' ){
        if (i == 61){
            *status = 1;
            return 0;
        }
        if (tmp[i]->letter == variable_name[name_index]){
            tmp = &tmp[i];
            name_index++;
            i = 0;
        }
        i++;
    }
    return tmp[i-1]->value;
}
unsigned int get_value_from_trie(string* valuable_name,trie* tr,int* status){
    return get_value_from_trie_inside(valuable_name->string,tr->root,status);

}


void add_to_string(string* str,char letter){
    char* tmp;
    if (str->current_size ==  str->size-2){
        str->size *= 2;
        tmp = realloc(str->string,sizeof(char)*str->size);
        if (tmp == NULL){
            memory_error();
        }
        str->string = tmp;
    }
    str->string[str->current_size] = letter;
    str->current_size++;
    str->string[str->current_size] = '\0';
}

string* create_string(int* status){
    string* str = (string*)malloc(sizeof(string));
    if (str == NULL){
        memory_error();
    }
    str->string = NULL;
    str->current_size = 0;
    str->string = (char*)malloc(sizeof(char)*10);
    if (str->string == NULL){
        *status = -2;
        return NULL;
    }
    str->size = 10;
    str->current_size = 0;
    return str;
}


void inverse(unsigned int* num){
    *num = ~(*num);
}
void delete_string(string* str){
    if (str == NULL){
        return;
    }
    free(str->string);
    free(str);
}
unsigned int strtouint(char* str,unsigned int base,int* status){
    char* end = NULL;
    unsigned long num;
    num = strtoul(str,&end,base);
    const int error = errno == ERANGE;
    if (error){
        *status = -5;
    }
    else if (num > 4294967295){
        *status = -5;
    }
    else if (end[0] != '\0'){
        *status = -6;
    }
    return num;
}
unsigned int input(unsigned int base_input,int* status){
    if ((base_input < 2) || (base_input > 36)){
        *status = -3;
        return 0;
    }
    char buff_str[33];
    scanf("%32s",buff_str);
    if (getchar() != '\n'){
        *status = -4;
        return 0;
    }
    *status = 0;
    unsigned int answer = strtouint(buff_str,base_input,status);
    if (*status < 0){
        return 0;
    }
    return answer;
}
void get_settings(FILE* file,unsigned int base_assign, unsigned int base_input, unsigned int base_output){
    if (file == NULL){
        return;
    }
    
}








