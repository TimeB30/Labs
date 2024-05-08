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
    (*array)[61]->is_used = 0;
    (*array)[61]->trie_nodes = NULL;
    char current_char = 48;
    for (int i = 0; i < 61; i++){
        (*array)[i] = (trie_node*)malloc(sizeof(trie_node));
        if ((*array)[i] == NULL){
            memory_error();
        }
        (*array)[i]->is_used = 0;
        (*array)[i]->trie_nodes = NULL;
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
        *status = -1;
        return;
    }
    unsigned int i = 0;
    unsigned int name_index = 0;
    trie_node** tmp = first_array;
    trie_node* tmp2;
    while (valuable_name[name_index] != '\0'){
        if (i == 61){
            *status = -1;
            return;
        }
        if (tmp[i]->letter == valuable_name[name_index]){
            name_index++;
            tmp2 = tmp[i];
            if (tmp[i]->trie_nodes == NULL){
                create_trie_node_array(&(tmp[i]->trie_nodes));
            }
            tmp = tmp[i]->trie_nodes;
            i = 0;
        }
        i++;
    }
    tmp2->value = value;
    tmp2->is_used = 1;
}

void add_value_to_trie(string* valuable_name, unsigned int value, trie* tr,int* status){
    add_value_to_trie_inside(valuable_name->string, value, tr->root,status);
}

trie_node* get_value_from_trie_inside(const char* variable_name,trie_node** first_array){
    if ((variable_name[0] > 47) && (variable_name[0] < 58)){
        return NULL;
    }
    unsigned int i = 0;
    unsigned int name_index = 0;
    trie_node** tmp = first_array;
    trie_node* tmp2;
    while(variable_name[name_index] != '\0' ){
        if (tmp == NULL){
            return NULL;
        }
        if (i == 61){
            return NULL;
        }
        if (tmp[i]->letter == variable_name[name_index]){
            tmp2 = tmp[i];
            tmp = tmp[i]->trie_nodes;
            name_index++;
            i = 0;
        }
        i++;
    }
    return tmp2;
}
trie_node* get_value_from_trie(string* valuable_name,trie* tr){
    return get_value_from_trie_inside(valuable_name->string,tr->root);

}


void add_to_string(string* str,char letter){
    char* tmp;
    if (str->size == 0){
        str->size = 10;
        str->string = (char*)malloc(sizeof(char)*str->size);
        if (str->string == NULL){
            memory_error();
        }
    }
    if (str->current_size ==  str->size-3){
        str->size *= 2;
        tmp = (char*)realloc(str->string,sizeof(char)*(str->size));
        if (tmp == NULL){
            memory_error();
        }
        str->string = tmp;
    }
    str->string[str->current_size] = letter;
    str->current_size++;
    str->string[str->current_size] = '\0';
}
void add_to_string_string(string* str,char* name){
    int i = 0;
    while (name[i] != '\0'){
        add_to_string(str,name[i]);
        i++;
    }
}
string* create_string(int* status){
    string* str = (string*)malloc(sizeof(string));
    if (str == NULL){
        *status = -2;
        return NULL;
    }
    str->string = (char*)malloc(sizeof(char)*10);
    if (str->string == NULL){
        *status = -2;
        return NULL;
    }
    str->size = 10;
    str->current_size = 0;
    return str;
}

void delete_string(string* str){
    if (str == NULL){
        return;
    }
    if (str->string != NULL){
        free(str->string);
    }
    free(str);
}
void inverse(unsigned int* num){
    *num = ~(*num);
}
void clear_string(string* str){
    if (str == NULL){
        return;
    }
    if (str->string == NULL){
        return;
    }
    str->current_size = 0;
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
void input(unsigned int* num,unsigned int base_input,string* error_message){
    int status = 0;
    if ((base_input < 2) || (base_input > 36)){
        add_to_string_string(error_message,"Wrong base\n");
        return ;
    }
    char buff_str[33];
    scanf("%32s",buff_str);
    if (getchar() != '\n'){
        add_to_string_string(error_message,"Too big number\n");
        return;
    }
    unsigned int answer = strtouint(buff_str,base_input,&status);
    if (status < 0){
        add_to_string_string(error_message,"Not number\n");
        return;
    }
    *num = answer;
}
void output(unsigned int* num,unsigned int base,string* error_message){
    int status;
    if ((base < 2) || (base > 36)){
        add_to_string_string(error_message,"wrong base\n");
        return;
    }
    unsigned int mods[33];
    int i = 0;
    while((*num) > 0){
        mods[i] = (*num) % base;
        (*num) /= base;
        i++;
    }
    for (int t = i - 1; t >= 0; t--){
        if (mods[t] < 10){
            printf("%c",mods[t] + 48);
        }
        else {
            printf("%c",mods[t] + 55);
        }
    }
    printf("\n");
}
//unsigned int output(void* num, void* base, void* not_used){
//    output_inside(*((unsigned int*)num),*((unsigned int*)base));
//    return 0;
//}
//unsigned int input(void* base,void* not_used, void* status){
//    return input_inside(*((unsigned int*)base),(int*)status);
//}
unsigned int  add(unsigned int num1, unsigned int num2,string* error_message){
    if (num1 > uint_max - num2){
        add_to_string_string(error_message,"Error: too big number\n");
        return num1;
    }
    return num1 + num2;
}
unsigned int mult(unsigned int num1, unsigned int num2,string* error_message){
    if ((num2 != 0) && (num1 < (uint_max / num2))){
        return num1 * num2;
    }
    add_to_string_string(error_message,"Error: too big number in result\n");
    return num1;
}
unsigned int sub(unsigned int num1, unsigned int num2,string* error_message){
    if (num2 > num1){
        add_to_string_string(error_message,"Error: second number is bigger than first, can't operate with negative numbers\n");
        return 0;
    }
    return num1 - num2;
}
unsigned int mod_pow(unsigned int base, unsigned int exp,string* error_message){
    unsigned int result = 1;
    while (exp > 0){
        if (exp % 2 == 1){
            result = (result * base) % uint_max;
        }
        base = (base * base) % uint_max;
        exp /= 2;
    }
    return result;
}
unsigned int my_div(unsigned int num1, unsigned int num2,string* error_message){
    if (num2 == 0){
        add_to_string_string(error_message,"Error: dividing by zero\n");
        return 0;
    }
    return num1/num2;
}
unsigned int rem(unsigned int num1, unsigned int num2,string* error_message){
    if (num2 == 0){
        add_to_string_string(error_message,"Error: dividing by zero\n");
        return 0;
    }
    return num1%num2;
}
unsigned int xor(unsigned int num1, unsigned int num2,string* error_message){
    return (num1 ^ num2);
}
unsigned int and(unsigned int num1, unsigned int num2,string* error_message){
    return num1 & num2;
}
unsigned int or(unsigned int num1, unsigned int num2,string* error_message){
    return num1 | num2;
}
unsigned int initialize(string* name,trie* tr,int* value){
    add_value_to_trie(name,*value,tr,0);
    return 0;
}
void not(unsigned int* num,unsigned int base,string* error_message){
     *num = ~(*num);
}
//unsigned int add(void* num1, void* num2,void* status){
//     return add_inside(*((unsigned int*)num1),*((unsigned int*)num2),(int*)status);
//}
//unsigned int mult(void* num1, void* num2,void* status){
//    return mult_inside(*((unsigned int*)num1),*((unsigned int*)num2),(int*)status);
//}
//unsigned int sub(void* num1, void* num2,void* status){
//    return sub_inside(*((unsigned int*)num1),*((unsigned int*)num2),(int*)status);
//}
//unsigned int mod_pow(void* base, void* exp, void* status){
//    return mod_pow_inside(*((unsigned int*)base),*((unsigned int*)exp),(int*)status);
//}
//unsigned int my_div(void* num1, void* num2,void* status){
//    return my_div_inside(*((unsigned int*)num1),*((unsigned int*)num2),(int*)status);
//}
//unsigned int rem(void* num1, void* num2,void* status){
//    return rem_inside(*((unsigned int*)num1),*((unsigned int*)num2),(int*)status);
//}
//unsigned int xor(void* num1, void* num2,void* status){
//    return xor_inside(*((unsigned int*)num1),*((unsigned int*)num2),(int*)status);
//}
//unsigned int and(void* num1, void* num2,void* status){
//    return and_inside(*((unsigned int*)num1),*((unsigned int*)num2),(int*)status);
//}
//unsigned int or(void* num1, void* num2,void* status){
//    return or_inside(*((unsigned int*)num1),*((unsigned int*)num2),(int*)status);
//}
//unsigned int initialize(void* new_name, void* tr,void* value){
//    return initialize_inside((string*)new_name,(trie*)tr,(int*)value);
//}
//unsigned int not(void* num1, void* num2,void* status){
//    return not_inside(*((unsigned int*)num1),1,NULL);
//}
void get_settings(FILE* file,unsigned int base_assign, unsigned int base_input, unsigned int base_output){
    if (file == NULL){
        return;
    }
    char command[6];
    fscanf(file,"%s",command);
    if (!strcmp(command,"add")){

    }

}

operations* create_operations(int* status){
    operations* ops = (operations*)malloc(sizeof(operations));
    if (ops == NULL){
        *status = -2;
        return NULL;
    }
    ops->operations_count =  13;
    ops->ops = (operation*)malloc(sizeof(operation)*ops->operations_count);
    if (ops->ops == NULL){
        *status = -2;
        free(ops);
        return NULL;
    }
    for (int i = 0;i < ops->operations_count; i++){
        ops->ops[i].name = create_string(status);
        ops->ops[i].realname = create_string(status);
        if ((ops->ops[i].name == NULL) || (ops->ops[i].realname == NULL)){
            *status = -2;
            return NULL;
        }
    }
    ops->ops[0].func = add;
    ops->ops[0].priority = 4;
    ops->ops[0].is_binary = 1;
    add_to_string_string(ops->ops[0].realname,"add");
    add_to_string_string(ops->ops[0].name,"add");
    ops->ops[1].func = mult;
    ops->ops[1].priority = 5;
    ops->ops[1].is_binary = 1;
    add_to_string_string(ops->ops[1].realname,"mult");
    add_to_string_string(ops->ops[1].name,"mult");
    ops->ops[2].func = sub;
    ops->ops[2].priority = 4;
    ops->ops[2].is_binary = 1;
    add_to_string_string(ops->ops[2].realname,"sub");
    add_to_string_string(ops->ops[2].name,"sub");
    ops->ops[3].func = mod_pow;
    ops->ops[3].priority = 6;
    ops->ops[3].is_binary = 1;
    add_to_string_string(ops->ops[3].realname,"pow");
    add_to_string_string(ops->ops[3].name,"pow");
    ops->ops[4].func = my_div;
    ops->ops[4].priority = 5;
    ops->ops[4].is_binary = 1;
    add_to_string_string(ops->ops[4].realname,"div");
    add_to_string_string(ops->ops[4].name,"div");
    ops->ops[5].func = rem;
    ops->ops[5].priority = 5;
    ops->ops[5].is_binary = 1;
    add_to_string_string(ops->ops[5].realname,"rem");
    add_to_string_string(ops->ops[5].name,"rem");
    ops->ops[6].func = xor;
    ops->ops[6].priority = 2;
    ops->ops[6].is_binary = 2;
    add_to_string_string(ops->ops[6].realname,"xor");
    add_to_string_string(ops->ops[6].name,"xor");
    ops->ops[7].func = and;
    ops->ops[7].priority = 3;
    ops->ops[7].is_binary = 1;
    add_to_string_string(ops->ops[7].realname,"and");
    add_to_string_string(ops->ops[7].name,"and");
    ops->ops[8].func = or;
    ops->ops[8].priority = 1;
    ops->ops[8].is_binary = 1;
    add_to_string_string(ops->ops[8].realname,"or");
    add_to_string_string(ops->ops[8].name,"or");
    ops->ops[9].func = not;
    ops->ops[9].priority = 7;
    ops->ops[9].is_binary = 0;
    add_to_string_string(ops->ops[9].realname,"not");
    add_to_string_string(ops->ops[9].name,"not");
    ops->ops[10].func = input;
    ops->ops[10].priority = 1;
    ops->ops[10].is_binary = 0;
    add_to_string_string(ops->ops[10].realname,"input");
    add_to_string_string(ops->ops[10].name,"input");
    ops->ops[11].func = output;
    ops->ops[11].priority = 0;
    ops->ops[11].is_binary = 0;
    add_to_string_string(ops->ops[11].realname,"output");
    add_to_string_string(ops->ops[11].name,"output");
//    ops->ops[12].func = initialize;
//    ops->ops[12].priority = 0;
//    add_to_string_string(ops->ops[9].realname,"=");
//    add_to_string_string(ops->ops[9].name,"=");
    return ops;
}
compile_options* create_compile_options(int* status){
    compile_options* opt = (compile_options*)malloc(sizeof(compile_options));
    if (opt == NULL){
        return NULL;
    }
    opt->str = (string**)malloc(sizeof(string*)*5);
    if (opt->str == NULL) {
        return NULL;
    }
    for (int i = 0; i < 2; i++){
        opt->str[i] = create_string(status);
        if (opt->str[i] == NULL){
            for (int t = 0; t < i; t++){
                delete_string(opt->str[t]);
            }
            return NULL;
        }
    }
    add_to_string_string(opt->str[0],"right=");
    add_to_string_string(opt->str[1],"op()");
    return opt;
}
void add_number_to_string(string* str,unsigned long int num){
    int letter = 0;
    int status;
    string* str_num = create_string(&status);
    while (num != 0){
        letter = num%10 + 48;
        add_to_string(str_num,letter);
        num /= 10;
    }
    for (unsigned int i = 0; i < str_num->current_size; i++){
        add_to_string(str,str_num->string[str_num->current_size-1-i]);
    }
    delete_string(str_num);
}
int get_full_str_and_check(string** str, FILE* file,unsigned long int* str_index,int* error_status,string* error_message,int* is_comment){
    (*str_index)++;
    *error_status = 0;
    clear_string(str[0]);
    clear_string(str[1]);
    str[0]->string[0] = '\n';
    int space_count = 0;
    int from_space = 1;
    char tmp;
    while ((tmp = fgetc(file)) != '\n') {
        if (tmp == EOF) {
            if (str[0]->current_size != 0) {
                return 1;
            }
            return EOF;
        }
        if ((tmp == '[') && (str[0]->current_size == 0)) {
            *is_comment = 1;
        } else if (tmp == ']') {
            if (*is_comment) {
                *is_comment = 0;
                continue;
            }
        }
        if (*is_comment) {
            continue;
        }
        clear_string(error_message);
        if ((tmp != ' ') && (tmp != '\t')) {
            from_space = 0;
            if (space_count == 0) {
                add_to_string(str[0], tmp);
            } else if (space_count == 1) {
                // can check for non alnum symbols
                add_to_string(str[1], tmp);
            } else {
                add_to_string_string(error_message, "Error on line ");
                add_number_to_string(error_message, *str_index);
                add_to_string_string(error_message, ": too many arguments\n");
                *error_status = 1;
                return 1;
            }
        } else if (tmp == ' ') {
            if (space_count < 2) {
                if (from_space) {
                    add_to_string_string(error_message, "Error on line ");
                    add_number_to_string(error_message, *str_index);
                    add_to_string_string(error_message, ": too many spaces\n");
                    *error_status = 1;
                    return 1;
                } else {
                    space_count++;
                }
            }
            from_space = 1;
        } else {
            if (space_count < 2) {
                if (from_space) {
                    add_to_string_string(error_message, "Error on line ");
                    add_number_to_string(error_message, *str_index);
                    add_to_string_string(error_message, ": tab symbol used\n");
                    *error_status = 1;
                    return 1;
                }
            }
        }
    }
    return 0;
}
int compare(string* str, char* str2){
    if (!strcmp(str->string,str2)){
        return 1;
    }
    return 0;
}
enum options options_recog(string** str,operations* ops){
    if (str[1]->current_size == 0){
        if (compare(str[0],"left=")){
            return left_value;
        }
        else if (compare(str[0],"right=")){
            return right_value;
        }
        else if (compare(str[0],"op()")){
            return postfix;
        }
        else if (compare(str[0],"(op)")){
            return infix;
        }
        else if (compare(str[0],"()op")){
            return prefix;
        }
        else{
            return error;
        }
    }
    else{
        for (int i = 0; i < 13; i++){
            if (!strcmp(str[1]->string,ops->ops[i].name->string)){
                return in_use;
            }
        }
        if (compare(str[0],"add")){
            return change_add;
        }
        else if (compare(str[0],"mult")){
            return change_mult;
        }
        else if (compare(str[0],"sub")){
            return change_sub;
        }
        else if (compare(str[0],"pow")){
            return change_pow;
        }
        else if (compare(str[0],"div")){
            return change_div;
        }
        else if (compare(str[0],"rem")){
            return change_rem;
        }
        else if (compare(str[0],"xor")){
            return change_xor;
        }
        else if (compare(str[0],"and")){
            return change_and;
        }
        else if (compare(str[0],"or")){
            return change_or;
        }
        else if (compare(str[0],"=")){
            return change_init;
        }
        else if (compare(str[0],"not")){
            return change_inverse;
        }
        else if (compare(str[0],"input")){
            return change_input;
        }
        else if (compare(str[0],"output")){
            return change_output;
        }
        else {
            return error;
        }
    }
}
void apply_settings(operations* ops,compile_options* comp_ops,FILE* file, int* status,string* error_message){
    if (file == NULL){
        file = fopen("backup.txt", "r");
        if (file == NULL){
            return;
        }
    }
    string* buff[2];
    buff[0] = create_string(status);
    buff[1] = create_string(status);
    int is_comment = 0;
    unsigned long int str_index = 0;
    int error_status = 0;
    while(get_full_str_and_check(buff, file,&str_index,&error_status,error_message,&is_comment) != EOF)  {
        if (error_status){
            return;
        }
        if ((buff[0]->string[0] == '#') || (buff[0]->string[0] == '\n') ){
            continue;
        }
        if (is_comment){
            continue;
        }
        switch (options_recog(buff,ops)) {
            case left_value:
                clear_string(comp_ops->str[0]);
                add_to_string_string(comp_ops->str[0],"left=");
                break;
            case right_value:
                clear_string(comp_ops->str[0]);
                add_to_string_string(comp_ops->str[0],"right=");
                break;
            case prefix:
                clear_string(comp_ops->str[1]);
                add_to_string_string(comp_ops->str[1],"()op");
                break;
            case infix:
                clear_string(comp_ops->str[1]);
                add_to_string_string(comp_ops->str[1],"(op)");
                break;
            case postfix:
                clear_string(comp_ops->str[1]);
                add_to_string_string(comp_ops->str[1],"op()");
                break;
            case change_add:
                clear_string(ops->ops->name);
                add_to_string_string(ops->ops[0].name,buff[1]->string);
                break;
            case change_mult:
                clear_string(ops->ops->name);
                add_to_string_string(ops->ops[1].name,buff[1]->string);
                break;
            case change_sub:
                clear_string(ops->ops->name);
                add_to_string_string(ops->ops[2].name,buff[1]->string);
                break;
            case change_pow:
                clear_string(ops->ops->name);
                add_to_string_string(ops->ops[3].name,buff[1]->string);
                break;
            case change_div:
                clear_string(ops->ops->name);
                add_to_string_string(ops->ops[4].name,buff[1]->string);
                break;
            case change_rem:
                clear_string(ops->ops->name);
                add_to_string_string(ops->ops[5].name,buff[1]->string);
                break;
            case change_xor:
                clear_string(ops->ops->name);
                add_to_string_string(ops->ops[6].name,buff[1]->string);
                break;
            case change_and:
                clear_string(ops->ops->name);
                add_to_string_string(ops->ops[7].name,buff[1]->string);
                break;
            case change_or:
                clear_string(ops->ops->name);
                add_to_string_string(ops->ops[8].name,buff[1]->string);
                break;
            case change_init:
                clear_string(ops->ops->name);
                add_to_string_string(ops->ops[9].name,buff[1]->string);
                break;
            case change_inverse:
                clear_string(ops->ops->name);
                add_to_string_string(ops->ops[10].name,buff[1]->string);
            case change_input:
                clear_string(ops->ops->name);
                add_to_string_string(ops->ops[11].name,buff[1]->string);
                break;
            case change_output:
                clear_string(ops->ops->name);
                add_to_string_string(ops->ops[12].name,buff[1]->string);
                break;
            case error:
                error_status = 1;
                clear_string(error_message);
                add_to_string_string(error_message,"Undefined reference '");
                add_to_string_string(error_message,buff[0]->string);
                add_to_string_string(error_message,"' at line ");
                add_number_to_string(error_message,str_index);
                add_to_string(error_message,'\n');
                return;
            case in_use:
                add_to_string_string(error_message,"Reference '");
                add_to_string_string(error_message,buff[1]->string);
                add_to_string_string(error_message,"' already in use, at line ");
                add_number_to_string(error_message,str_index);
                return;
        }


    }
    delete_string(buff[0]);
    delete_string(buff[1]);

}
enum run_errors check_variable(string* variable_name){
    if ((variable_name->string[0] > 47) && (variable_name->string[0] < 58)){
        return name_error;
    }
    for (int i = 0; i < variable_name->current_size; i++){
        if (!((isalnum(variable_name->string[i])) || (variable_name->string[i] == '_'))){
            return name_error;
        }

    }
    return good_name;
}
operation * get_op_info(string* func_name,operations* ops){
    for (int i = 0; i < 12; i++){
        if (!strcmp(func_name->string,ops->ops[i].name->string)){
            return &(ops->ops[i]);
        }
    }
    return NULL;
};
int init_empty_val(trie* tr,string* variable_name,string* error_message,unsigned long int str_index){
    clear_string(error_message);
    int status = 0;
    trie_node* variable_info;
    if (check_variable(variable_name) == good_name) {
        if (!strcmp(variable_name->string, "BREAKPOINT")) {
            add_to_string_string(error_message, "Error: BREAKPOINT is reserved name");
            add_number_to_string(error_message, str_index);
            add_to_string(error_message, '\n');
            return 0;
        }
        variable_info = get_value_from_trie(variable_name, tr);
        if (variable_info == NULL) {
            add_value_to_trie(variable_name, 0, tr, &status);
            return 1;
            if (status < 0) {
                add_to_string_string(error_message, "Error: Memory allocation error");
                add_number_to_string(error_message, str_index);
                add_to_string(error_message, '\n');
                return 0;
            }
        }
        else if (variable_info->is_used) {
            add_to_string_string(error_message, "Error: variable '");
            add_to_string_string(error_message,variable_name->string);
            add_to_string_string(error_message, "' already exist at line ");
            add_number_to_string(error_message, str_index);
            add_to_string(error_message, '\n');
            return 0;
        }
        else {
            add_value_to_trie(variable_name, 0, tr, &status);
            add_to_string_string(error_message, "Error: Memory allocation error");
            add_number_to_string(error_message, str_index);
            add_to_string(error_message, '\n');
            return 0;
        }
    }
    else {
        add_to_string_string(error_message, "Error: wrong variable name '");
        add_to_string_string(error_message,variable_name->string);
        add_to_string_string(error_message,"' at line ");
        add_number_to_string(error_message, str_index);
        add_to_string(error_message, '\n');
        return 0;
    }
    //TODO зарезервировать BREAKPOINT чтобы не было обьявлено переменной с таким именем
}
unsigned int* equation_recog(string* equation,operations* ops, compile_options* comp_ops,trie* variables_data,unsigned int* answer,
                             unsigned int base_assign, unsigned int base_input,unsigned int base_output,
                             unsigned int* i,int* status,int* after_func,int is_binary,string* error_message,unsigned int str_index){
//    if (*status < 0){
//        return NULL;
//    }
    *status = 0;
    clear_string(error_message);
    unsigned int* check;
//    if (equation->string[*i] == ';'){
//        add_to_string_string(error_message, "Error: too few arguments was given at line");
//        add_number_to_string(error_message, str_index);
//        add_to_string(error_message, '\n');
//        *status = -1;
//        return NULL;
//    }
    string* buff_str = create_string(status);
    if (*status < 0){
        add_to_string_string(error_message, "Memory allocation error at line");
        add_number_to_string(error_message, str_index);
        add_to_string(error_message,'\n');
        return NULL;
    }
    operation* op;
    unsigned int num = 0;
    int after_func2 = 0;
    unsigned int base;
    trie_node* variable_info;
    unsigned int param1;
    unsigned int param2;
    while (*i < equation->current_size){
        if ((equation->string[*i] == '(')){
            op = get_op_info(buff_str,ops);
            if (op == NULL){
                add_to_string_string(error_message, "Error: function named '");
                add_to_string_string(error_message,buff_str->string);
                add_to_string_string(error_message, "' not found at line");
                add_number_to_string(error_message, str_index);
                add_to_string(error_message, '\n');
//                *status = -1;
                delete_string(buff_str);
                return NULL;
            }
            else{
                *after_func = 1;
                (*i)++;
                if (op->is_binary){
                    check = equation_recog(equation,ops,comp_ops,variables_data,answer,base_assign,base_input,base_output,i,status,&after_func2,1,error_message,str_index);
                    if (check == NULL){
                        delete_string(buff_str);
                        return NULL;
                    }
                    param1 = *check;
                    check = equation_recog(equation,ops,comp_ops,variables_data,answer,base_assign,base_input,base_output,i,status,&after_func2,1,error_message,str_index);
                    if (check == NULL){
                        delete_string(buff_str);
                        return NULL;
                    }
                    param2 = *check;
                    *answer = ((unsigned int (*) (unsigned int, unsigned int, string*))op->func)(param1,param2,error_message);
                    if (error_message->current_size > 0){
                        add_to_string_string(error_message,"at line ");
                        add_number_to_string(error_message,str_index);
                        add_to_string(error_message,'\n');
//                        *status = -1;
                        delete_string(buff_str);
                        return NULL;
                    }

                }
                else{
                    if (!strcmp(op->realname->string,"input")){
                        base = base_input;
                    }
                    else{
                        base = base_output;
                    }
                    check = equation_recog(equation,ops,comp_ops,variables_data,answer,base_assign,base_input,base_output,i,status,&after_func2,0,error_message,str_index);
                    if (check == NULL){
                        delete_string(buff_str);
                        return NULL;
                    }
                     ((void (*) (unsigned int*, unsigned int,string*))op->func)(check,base,error_message);
                    if (error_message->current_size > 0){
                        add_to_string_string(error_message,"at line ");
                        add_number_to_string(error_message,str_index);
                        add_to_string(error_message,'\n');
//                        *status = -1;
                        delete_string(buff_str);
                        return NULL;
                    }
                }
                delete_string(buff_str);
                return answer;
            }

        }
        else if (equation->string[*i] == ','){
            //TODO наверное если после завершения программы i < current_size значит было передано больше параметров чем 1 или 2  проверить! на первый тест так и работает без подсчета запятых но почему ?
            if (is_binary) {
                if (*after_func) {
                    *after_func = 0;
                    clear_string(buff_str);
                    (*i)++;
                    continue;
                }
                else {
                    (*i)++;
                    *answer = strtouint(buff_str->string, base_assign, status);
                    if (*status < 0) {
//                        *status = 0;
                        variable_info = get_value_from_trie(buff_str,variables_data);
                        if ((variable_info != NULL) && (variable_info->is_used)){
                            delete_string(buff_str);
                            return &(variable_info->value);
                        }
                        add_to_string_string(error_message, "Error: parameter '");
                        add_to_string_string(error_message,buff_str->string);
                        add_to_string_string(error_message, "' is not a number or variable at line");
                        add_number_to_string(error_message, str_index);
                        //TODO сделать  проверку переменной и добавить в поле значение была эта переменная обьявлена или нет чтоб не обратиться к необьявленной переменной или обьявить одну и ту же переменную дважды
                        add_to_string(error_message, '\n');
//                        *status = -1;
                        delete_string(buff_str);
                        return NULL;
                    }
                    else {
                        delete_string(buff_str);
                        return answer;
                    }
                }
            }
            else {
                add_to_string_string(error_message, " expected ( or too many arguments  at line ");
                add_number_to_string(error_message, str_index);
                add_to_string(error_message, '\n');
//                *status = -1;
                delete_string(buff_str);
                return NULL;
            }
        }
        else if (equation->string[*i] == ')'){
            if (buff_str->current_size == 0){
                add_to_string_string(error_message, "Error: no parameter given at line ");
                add_number_to_string(error_message, str_index);
                add_to_string(error_message, '\n');
//                *status = -1;
                delete_string(buff_str);
                return NULL;
            }
            if (*after_func) {
                (*i)++;
                clear_string(buff_str);
                continue;
            }
            else {
                (*i)++;
                *answer = strtouint(buff_str->string,base_assign,status);
                if (*status < 0){
//                    *status = 0;
                    variable_info = get_value_from_trie(buff_str,variables_data);
                    if ((variable_info != NULL) && (variable_info->is_used)){
                        delete_string(buff_str);
                        return &(variable_info->value);
                    }
                    add_to_string_string(error_message, "Error: parameter '");
                    add_to_string_string(error_message,buff_str->string);
                    add_to_string_string(error_message, "' is not a number or variable at line");
                    add_number_to_string(error_message, str_index);
                    //TODO сделать  проверку переменной и добавить в поле значение была эта переменная обьявлена или нет чтоб не обратиться к необьявленной переменной или обьявить одну и ту же переменную дважды
                    add_to_string(error_message, '\n');
//                    *status = -1;
                    delete_string(buff_str);
                    return NULL;
                }
                else {
                    delete_string(buff_str);
                    return answer;
                }
            }

        }
        add_to_string(buff_str,equation->string[*i]);
        (*i)++;
    }
    if (buff_str->current_size == 0){
        add_to_string_string(error_message, "Error: expected more variable or num at line ");
        add_number_to_string(error_message, str_index);
        add_to_string(error_message,'\n');
        return NULL;
    }
    *answer = strtouint(equation->string,base_assign,status);
    if (*status < 0){
        variable_info = get_value_from_trie(buff_str,variables_data);
        if ((variable_info != NULL) && (variable_info->is_used)){
            delete_string(buff_str);
//            *status = 0;
            return &(variable_info->value);
        }
        add_to_string_string(error_message, "Error: '");
        add_to_string_string(error_message,equation->string);
        add_to_string_string(error_message, "' is not a number, variable or function at line");
        add_number_to_string(error_message, str_index);
        add_to_string(error_message,'\n');
        delete_string(buff_str);
        return NULL;
    }
    delete_string(buff_str);
    return answer;
}
int check_rvalue(string* str_to_write,FILE* file,string* error_message,unsigned long int* str_index,char* letter){
    if ((str_to_write == NULL) || (file == NULL) || (error_message == NULL)){
        return  1;
    }
    int from_letter = 0;
    int separater_met = 1;
    while ((*letter = fgetc(file)) != EOF){
        if ((*letter == ' ') || (*letter == '\t')){
            if(from_letter){
                separater_met = 0;
            }
            from_letter = 0;
            continue;
        }
        if (*letter == '\n'){
            (*str_index)++;
            if(from_letter){
                separater_met = 0;
            }
            from_letter = 0;
            continue;

        }
        if ((*letter == '(') || (*letter == ',')){
            separater_met = 1;
            continue;
        }
        if (*letter == ';'){
            return 1;
        }
        if (separater_met == 0){
            add_to_string_string(error_message,"Error: function or variable name error at line ");
            add_to_string_string(error_message,str_to_write->string);
            add_to_string(error_message,'\n');
            return 0;
        }
        add_to_string(str_to_write,*letter);
        from_letter = 1;
    }
    return 1;
}
//enum run_errors read_line(operations* ops, compile_options* comp_ops,trie* variables_data,unsigned int* answer,string** buff,FILE* file,unsigned long int* str_index,string* error_message,unsigned int base_assign, unsigned int base_input, unsigned int base_output) {
//    clear_string(error_message);
//    if (file == NULL) {
//        return 0;
//    }
//    char letter;
//    clear_string(buff[0]);
//    clear_string(buff[1]);
//    clear_string(buff[2]);
//    int status = 0;
//    int after_func = 0;
//    int is_comment = 0;
//    int is_line_comment = 0;
//    int skip_space = 1;
//    unsigned long int from_letter = 0;
//    int i = 0;
//    unsigned int k = 0;
//    string *str_to_write = buff[0];
//    while ((letter = fgetc(file)) != EOF) {
////        if (letter == ']'){
////            is_comment = 0;
//            continue;
//        }
//        else if (is_comment){
//            if (letter == '\n'){
//                (*str_index)++;
//                if (is_line_comment){
//                    is_line_comment = 0;
//                    is_comment = 0;
//                }
//            }
//            continue;
//        }
//        else if (letter == ' ') {
//            if (from_letter == 1) {
//                if (str_to_write == buff[0]) {
//                    str_to_write = buff[1];
//                    from_letter = 0;
//                }
//            }
//            if (skip_space){
//                continue;
//            }
//            add_to_string(str_to_write,letter);
//        }
//        else if (letter == '\t') {
//            continue;
//        }
//        else if (letter == '\n') {
//            (*str_index)++;
//            continue;
//        }
//        else if (letter == '['){
//            is_comment = 1;
//            continue;
//        }
//        else if (letter == '#'){
//            is_line_comment = 1;
//            is_comment = 1;
//            continue;
//        }
//        else if (letter == '=') {
//            if (str_to_write == buff[0]) {
//                str_to_write = buff[1];
//            } else if (buff[1]->current_size > 0) {
//                add_to_string_string(error_message, "Error: wrong variable name at  line: ");
//                add_number_to_string(error_message, *str_index);
//                add_to_string(error_message, '\n');
//                return run_error;
//            }
//            add_to_string(str_to_write, letter);
//            str_to_write = buff[2];
//            if (!check_rvalue(str_to_write,file,error_message,str_index,&letter)){
//                 return run_error;
//            }
//        }
//        if (letter == ';') {
//            if ((buff[1]->current_size == 0) && (buff[2]->current_size == 0)) {
//                if (equation_recog(buff[0],ops,comp_ops,variables_data,answer,base_assign,base_input,base_output,&k,&status,&after_func,0,error_message,*str_index) == NULL){
//                    if (init_empty_val(variables_data,buff[0],error_message,*str_index)){
//                        return init;
//                    }
//                    clear_string(error_message);
//                    add_to_string_string(error_message,"Error: wrong variable name or check function '");
//                    add_to_string_string(error_message,buff[0]->string);
//                    add_to_string_string(error_message,"' at line ");
//                    add_number_to_string(error_message, *str_index);
//                    add_to_string(error_message, '\n');
//                    return run_error;
//                }
//                else{
//                    return init;
//                }
//            } else if ((buff[2]->current_size > 0) && (buff[1]->current_size == 0)) {
//                add_to_string_string(error_message, "Error: expected = at  line: ");
//                add_number_to_string(error_message, *str_index);
//                add_to_string(error_message, '\n');
//                return run_error;
//            } else if ((buff[1]->current_size > 0) && (buff[2]->current_size == 0)) {
//                add_to_string_string(error_message, "Error: expected rvalue at  line: ");
//                add_number_to_string(error_message, *str_index);
//                add_to_string(error_message, '\n');
//                return run_error;
//            }
//            else if (buff[0]->current_size == 0){
//                add_to_string_string(error_message, "Error: expected variable name  at  line: ");
//                add_number_to_string(error_message, *str_index);
//                add_to_string(error_message, '\n');
//                return run_error;
//            }
//            else {
////                add_to_string(str_to_write, letter);
//                if (equation_recog(buff[2],ops,comp_ops,variables_data,answer,base_assign,base_input,base_output,&k,&status,&after_func,0,error_message,*str_index) == NULL){
//                    return run_error;
//                }
////                if (status < 0){
////                    return run_error;
////                }
//                if (k < buff[2]->current_size){
//                    return too_many_arguments;
//                    //TODO если передать переменную как парамет через пробел то он это съест потому что пробелы убираются бляяяяя
//                }
//                return success;
//            }
//        }
//        from_letter = 1;
//        add_to_string(str_to_write, letter);
//
//    }
//    if (buff[0]->current_size == 0){
//        return end;
//    }
//    add_to_string_string(error_message, "Error: expected ; or ] line: ");
//    add_number_to_string(error_message, *str_index);
//    add_to_string(error_message, '\n');
//    return run_error;
//}
enum run_errors read_line(operations* ops, compile_options* comp_ops,trie* variables_data,unsigned int* answer,string** buff,FILE* file,unsigned long int* str_index,string* error_message,unsigned int base_assign, unsigned int base_input, unsigned int base_output) {
    clear_string(error_message);
    if (file == NULL) {
        return 0;
    }
    char letter;
    clear_string(buff[0]);
    clear_string(buff[1]);
    clear_string(buff[2]);
    int status = 0;
    int after_func = 0;
    int is_comment = 0;
    int is_line_comment = 0;
    int func_closed = 1;
    int separater_met = 1;
    unsigned long int from_letter = 0;
    int i = 0;
    unsigned int k = 0;
    string *str_to_write = buff[0];
    while ((letter = fgetc(file)) != EOF){
        if (letter == ']'){
            is_comment = 0;
            continue;
        }
        else if (is_comment){
            if (letter == '\n'){
                (*str_index)++;
                if (is_line_comment){
                    is_line_comment = 0;
                    is_comment = 0;
                }
            }
            continue;
        }
        if (letter == '['){
            is_comment = 1;
            continue;
        }
        if (letter == '#'){
            is_comment = 1;
            is_line_comment = 1;
            continue;
        }
        if ((letter == ' ') || (letter == '\t')){
            if(from_letter){
                separater_met = 0;
            }
            from_letter = 0;
            continue;
        }
        if (letter == '\n'){
            (*str_index)++;
            if(from_letter){
                separater_met = 0;
            }
            from_letter = 0;
            continue;

        }
        if (letter == '='){
            if (str_to_write == buff[2]){
                add_to_string_string(error_message,"Error: second '=' met at lone");
                add_number_to_string(error_message, *str_index);
                add_to_string(error_message, '\n');
                return run_error;
            }
            separater_met = 1;
            add_to_string(buff[1],letter);
            str_to_write = buff[2];
            continue;
        }
        if ((letter == ',') || (letter == '(') || (letter == ')')){
            add_to_string(str_to_write,letter);
            from_letter = 0;
            separater_met = 1;
            continue;
        }
        if (letter == ';'){
            if ((buff[1]->current_size == 0) && (buff[2]->current_size == 0)) {
                if (equation_recog(buff[0],ops,comp_ops,variables_data,answer,base_assign,base_input,base_output,&k,&status,&after_func,0,error_message,*str_index) == NULL){
                    if (init_empty_val(variables_data,buff[0],error_message,*str_index)){
                        return init;
                    }
                    clear_string(error_message);
                    add_to_string_string(error_message,"Error: wrong variable name or check function '");
                    add_to_string_string(error_message,buff[0]->string);
                    add_to_string_string(error_message,"' at line ");
                    add_number_to_string(error_message, *str_index);
                    add_to_string(error_message, '\n');
                    return run_error;
                }
                else{
                    return init;
                }
            } else if ((buff[2]->current_size > 0) && (buff[1]->current_size == 0)) {
                add_to_string_string(error_message, "Error: expected = at  line: ");
                add_number_to_string(error_message, *str_index);
                add_to_string(error_message, '\n');
                return run_error;
            } else if ((buff[1]->current_size > 0) && (buff[2]->current_size == 0)) {
                add_to_string_string(error_message, "Error: expected rvalue at  line: ");
                add_number_to_string(error_message, *str_index);
                add_to_string(error_message, '\n');
                return run_error;
            }
            else if (buff[0]->current_size == 0){
                add_to_string_string(error_message, "Error: expected variable name  at  line: ");
                add_number_to_string(error_message, *str_index);
                add_to_string(error_message, '\n');
                return run_error;
            }
            else {
//                add_to_string(str_to_write, letter);
                if (equation_recog(buff[2],ops,comp_ops,variables_data,answer,base_assign,base_input,base_output,&k,&status,&after_func,0,error_message,*str_index) == NULL){
                    return run_error;
                }
//                if (status < 0){
//                    return run_error;
//                }
                if (k < buff[2]->current_size){
                    return too_many_arguments;
                    //TODO если передать переменную как парамет через пробел то он это съест потому что пробелы убираются бляяяяя
                }
                return success;
            }
        }
        if (separater_met == 0){
            add_to_string_string(error_message,"Error: function or variable name error at line ");
            add_number_to_string(error_message,*str_index);
            add_to_string(error_message,'\n');
            return run_error;
        }
        add_to_string(str_to_write,letter);
        from_letter = 1;
    }
    if (buff[0]->current_size == 0){
        return end;
    }
    add_to_string_string(error_message, "Error: expected ; or ] line: ");
    add_number_to_string(error_message, *str_index);
    add_to_string(error_message, '\n');
    return run_error;
}
void run(operations* ops,compile_options* comp_ops,FILE* run_file, int debug_status,string* error_message,trie* variables_data,unsigned int base_assign, unsigned int base_input,unsigned int base_output){
    unsigned long int str_index = 1;
    clear_string(error_message);
    if (run_file == NULL){
        return ;
    }
    int status;
    unsigned int answer = 0;
    trie_node* variable_info;
    trie_node* variable_info2;
    int i = 0;
    string* buff[3] = {create_string(&status), create_string(&status),create_string(&status)};
    enum run_errors a;
        while ((a = read_line(ops,comp_ops,variables_data,&answer,buff,run_file,&str_index,error_message,base_assign,base_input,base_output)) != run_error){
            switch(a){
                case success:
                    printf("success\n");
                    if (check_variable(buff[0]) == good_name) {
                        if (!strcmp(buff[0]->string, "BREAKPOINT")) {
                            add_to_string_string(error_message, "Error: BREAKPOINT is reserved name");
                            add_number_to_string(error_message, str_index);
                            add_to_string(error_message, '\n');
                            return;
                        }
                        add_value_to_trie(buff[0], answer, variables_data, &status);
                    }
                    else{
                        add_to_string_string(error_message, "Error: wrong variable name");
                        add_number_to_string(error_message, str_index);
                        add_to_string(error_message, '\n');
                        return;
                    }
                    break;
                case empty:
                    printf("empty file\n");
                    break;
                case too_many_arguments:
                    printf("too many\n");
                    break;
                case init_val:
                    printf("init val\n");
                    if (check_variable(buff[2]) == good_name) {
                        variable_info = get_value_from_trie(buff[2], variables_data);
                        if ((variable_info == NULL) || (!variable_info->is_used)) {
                            add_to_string_string(error_message, "Error: ");
                            add_to_string_string(error_message, buff[2]->string);
                            add_to_string_string(error_message, " is not variable at line");
                            add_number_to_string(error_message, str_index);
                            add_to_string(error_message, '\n');
                            return;
                        } else {
                            add_value_to_trie(buff[0], variable_info->value, variables_data, &status);
                        }
                    }
                    else{
                        add_to_string_string(error_message, "Error: wrong variable name");
                        add_number_to_string(error_message, str_index);
                        add_to_string(error_message, '\n');
                        return;
                    }
                    break;
                case end:
                    return;
            }
        }
}