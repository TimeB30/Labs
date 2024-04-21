#include"func.h"

void memory_error(){
    perror("Memory allocation error\n");
    exit(EXIT_FAILURE);
}
enum heap_data_types data_type_recog(departments_option* dep){
    char* data_type = dep->data_type;
    if (!strcmp(data_type,"HashSet")){
        return HashSet;
    }
    else if (!strcmp(data_type,"DynamicArray")){
        return DynamicArray;
    }
    else if (!strcmp(data_type,"BinarySearchTree")){
        return BinarySearchTree;
    }
    else if (!strcmp(data_type,"Trie")){
        return Trie;
    }
    return None;
}
enum heap_data_types heap_type_recog(departments_option* dep){
    char* heap_type = dep->heap_type;
    if (!strcmp(heap_type,"BinaryHeap")){
        return BinaryHeap;
    }
    else if (!strcmp(heap_type,"BinomialHeap")){
        return BinomialHeap;
    }
    else if (!strcmp(heap_type,"FibonacciHeap")){
        return FibonacciHeap;
    }
    else if (!strcmp(heap_type,"SkewHeap")){
        return SkewHeap;
    }
    else if (!strcmp(heap_type,"LeftistHeap")){
        return LeftistHeap;
    }
    else if (!strcmp(heap_type,"Treap")){
        return Treap;
    }
    return None;
}



//int compare_dates(int* date1, int* date2){
//    int year = date1[0] - date2[0];
//    if ()
//}
int str_to_unsigned_int(char* str, unsigned int* num){
    char* end;
    *num = strtoul(str,&end,10);
    const int error = errno == ERANGE;
    if (errno){
        return 1;
    }
    else if (end[0] != 0){
        return 1;
    }
    return 0;
}
int str_to_double(char* str, double* num){
    char* end;
    *num = strtod(str,&end);
    const int error = errno == ERANGE;
    if (errno){
        return 1;
    }
    else if (end[0] != 0){
        return 1;
    }
    return 0;
}
int check_files(int argc, char** argv){
    for (int i = 2; i < argc; i++){
        char* file_name = argv[i];
        FILE* file = fopen(file_name, "r");
        if (file == NULL){
            return 1;
        }
        else{
            fclose(file);
        }
    }
    return 0;
}



void siftUp(binary_heap* b_heap,int index){
    int i = index;
    int parent = (i-1)/2;
    binary_heap_node buff;
    while(1){
        if (b_heap->heap[parent].priority < b_heap->heap[i].priority){
            buff = b_heap->heap[i];
            b_heap->heap[i] = b_heap->heap[parent];
            b_heap->heap[parent] = buff;
            i = parent;
            parent = (i-1)/2;
        }
        else if (b_heap->heap[parent].priority == b_heap->heap[i].priority){
            if (b_heap->heap[i].date_time < b_heap->heap[parent].date_time){
                buff = b_heap->heap[i];
                b_heap->heap[i] = b_heap->heap[parent];
                b_heap->heap[parent] = buff;
                i = parent;
                parent = (i-1)/2;
            }
            else{
                break;
            }
        }
       else{
           break;
       }
    }

}

void siftDown(binary_heap* b_heap,int index){
    int left = 2*index + 1;
    int right = 2*index + 2;
    int node_to_switch = left;
    int current_size = b_heap->current_size;
    binary_heap_node buff;
    if (left > current_size){
        return;
    }
    if (((right <= current_size)) && (b_heap->heap[right].priority > b_heap->heap[left].priority)){
        node_to_switch = right;
    }
    else if (b_heap->heap[left].priority == b_heap->heap[right].priority){
        if (b_heap->heap[left].date_time > b_heap->heap[right].date_time){
            node_to_switch = right;
        }
    }
    if ((b_heap->heap[index].priority >= b_heap->heap[node_to_switch].priority) && (b_heap->heap[index].date_time <= b_heap->heap[node_to_switch].date_time)){
        return;
    }
    buff = b_heap->heap[index];
    b_heap->heap[index] = b_heap->heap[node_to_switch];
    b_heap->heap[index] = buff;
    siftDown(b_heap,node_to_switch);
}
void add_elem_to_binary_heap(unsigned int priority,time_t date_time, unsigned int appln_id,char* application_text,binary_heap* b_heap){
    binary_heap_node * buff = NULL;
    b_heap->current_size++;
    if (b_heap->current_size == b_heap->size){
        b_heap->size += 10;
        buff = (binary_heap_node*)realloc(b_heap->heap,sizeof(binary_heap_node)*b_heap->size);
        if (buff == NULL){
            memory_error();
        }
        b_heap->heap = buff;
    }
    if (b_heap->current_size == 10){
        printf("blya\n");
    }
    b_heap->heap[b_heap->current_size].application_id = appln_id;
    b_heap->heap[b_heap->current_size].priority = priority;
    b_heap->heap[b_heap->current_size].date_time = date_time;
    b_heap->heap[b_heap->current_size].application_text = (char*)malloc(sizeof(char)*(strlen(application_text)+1));
    if (b_heap->heap[b_heap->current_size].application_text == NULL){
        memory_error();
    }
    strcpy(b_heap->heap[b_heap->current_size].application_text,application_text);
    siftUp(b_heap,b_heap->current_size);

}
void add_elem_to_binary_heap_interface(unsigned int priority, time_t date_time, unsigned int appln_id, char* application_text, void* b_heap){
    add_elem_to_binary_heap(priority,date_time,appln_id,application_text,(binary_heap*)b_heap);
}
binary_heap* create_binary_heap(){
    binary_heap* b_heap = (binary_heap*)malloc(sizeof(binary_heap));
    if (b_heap == NULL){
        perror("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    b_heap->size = 10;
    b_heap->current_size = -1;
    b_heap->heap = (binary_heap_node*)malloc(sizeof(binary_heap_node) * b_heap->size);
    if (b_heap->heap == NULL){
        perror("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return b_heap;
}
void* create_binary_heap_interface(){
    return create_binary_heap();
}
void merge_binary_heaps(binary_heap* heap1, binary_heap* heap2){
    if ((heap1 == NULL) || (heap2 == NULL)){
        return;
    }
    int i = 0;
    while(i <= heap2->current_size){
        add_elem_to_binary_heap(heap2->heap[i].priority,heap2->heap[i].date_time,heap2->heap[i].application_id,heap2->heap[i].application_text,heap1);
        i++;
    }
}
void merge_binary_heaps_interface(void* heap1, void* heap2){
    merge_binary_heaps((binary_heap*)heap1,(binary_heap*)heap2);
}
void delete_binary_heap(binary_heap** heap){
    for (int i = 0; i <= (*heap)->current_size; i++){
        free((*heap)->heap[i].application_text);
    }
    free((*heap)->heap);
    (*heap)->heap = NULL;
    free(*heap);
    (*heap) = NULL;
}
void* get_binary_max(binary_heap* heap){
    return heap->heap;
}
unsigned int get_application_id_binary_node(binary_heap_node* node){
    return node->application_id;
}
void remove_binary_max(binary_heap* b_heap){
    if (b_heap->current_size == -1){
        return;
    }
    unsigned int result = b_heap->heap[0].priority;
    b_heap->heap[0] = b_heap->heap[b_heap->current_size];
    b_heap->current_size--;
    siftDown(b_heap,0);
}
binary_heap_node* get_max_binary_heap(binary_heap* b_heap){
    if (b_heap->current_size > -1){
        return &b_heap->heap[0];
    }
    return NULL;
}
void parse_time(FILE* file, struct tm* tm_struct){
    fscanf(file,"%d-%d-%d %d:%d:%d",&(tm_struct->tm_year),&(tm_struct->tm_mon),&(tm_struct->tm_mday),&(tm_struct->tm_hour),&(tm_struct->tm_min),&(tm_struct->tm_sec));
    tm_struct->tm_year -= 1900;
    tm_struct->tm_mon -= 1;
//    tm_struct->tm_hour -= 1;
//    tm_struct->tm_min -=  1;
//    tm_struct->tm_sec -= 1;
    tm_struct->tm_gmtoff = 0;
    tm_struct->tm_wday = 0;
    tm_struct->tm_yday = 0;
    tm_struct->tm_isdst = 0;
    tm_struct->tm_zone = 0;
}
void print_date_time(struct tm* date_time){
    printf("%d-%d-%d %d:%d:%d\n",date_time->tm_year,date_time->tm_mon,date_time->tm_mday,date_time->tm_hour,date_time->tm_min,date_time->tm_sec);
}
int create_departments_option(departments_option** dep,FILE* file) {
    struct tm tm_struct;
    *dep = (departments_option*) malloc(sizeof(departments_option ));
    char *end;
    if (*dep == NULL) {
        perror("Ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
    }
    (*dep)->max_priority = 0;
    (*dep)->heap_type = (char *) malloc(sizeof(char) * 14);
    (*dep)->data_type = (char *) malloc(sizeof(char) * 17);
//    if (((*dep)->start_date_time == NULL) || ((*dep)->end_date_time == NULL) || ((*dep)->heap_type == NULL) ||
//        ((*dep)->data_type == NULL)) {
//        memory_error();
//    }
    char *convert_buff = (char *) malloc(sizeof(char) * 20);
    if (convert_buff == NULL) {
            memory_error();
        }
    fscanf(file, "%s", (*dep)->heap_type);
    fscanf(file, "%s", (*dep)->data_type);
    parse_time(file,&tm_struct);
//    print_date_time(&tm_struct);
    (*dep)->start_date_time = mktime(&tm_struct);
    parse_time(file,&tm_struct);
    (*dep)->end_date_time = mktime(&tm_struct);
    fscanf(file, "%s", convert_buff);
    (*dep)->min_processing_time = strtoul(convert_buff, &end, 10);
    fscanf(file, "%s", convert_buff);
    (*dep)->max_processing_time = strtoul(convert_buff, &end, 10);
    fscanf(file, "%s", convert_buff);
    (*dep)->departments_quantity = strtoul(convert_buff, &end, 10);
    (*dep)->operators_quantity = (unsigned int *) malloc(sizeof(unsigned int) * (*dep)->departments_quantity);
    if ((*dep)->operators_quantity == NULL) {
        memory_error();
    }
    for (int i = 0; i < (*dep)->departments_quantity; i++) {
        fscanf(file, "%s", convert_buff);
        (*dep)->operators_quantity[i] = strtoul(convert_buff, &end, 10);
    }
    fscanf(file, "%s", convert_buff);
    (*dep)->overload_coefficient = strtod(convert_buff, &end);
    free(convert_buff);
    return 0;
}



binomial_heap* create_binomial_heap(){
    binomial_heap* binom_heap = (binomial_heap*)malloc(sizeof(binomial_heap));
    if (binom_heap == NULL){
        memory_error();
    }
    binom_heap->last_node = NULL;
    binom_heap->max = NULL;
    return binom_heap;
}
void merge_binomial_nodes(binomial_node* node1, binomial_node* node2){
    node1->rank++;
    if (node2->previous != NULL) {
        node2->previous->next = node2->next;
    }
    if (node2->next != NULL) {
        node2->next->previous = node2->previous;
    }
    if (node1->sons == NULL){
        node1->sons = node2;
        node2->previous = NULL;
    }
    else {
        node1->sons->next = node2;
        node2->previous = node1->sons;
        node1->sons = node1->sons->next;
    }
    node2->next = NULL;
}
void set_min_in_binom_heap(binomial_heap* binom_heap){
    binomial_node* carriage_node = binom_heap->last_node;
    while(carriage_node != NULL){
        if (binom_heap->max->priority < carriage_node->priority){
            binom_heap->max = carriage_node; // проверить
        }
        else if (binom_heap->max->priority == carriage_node->priority){
            if (binom_heap->max->date_time > carriage_node->date_time){
                binom_heap->max = carriage_node;
            }
        }
// сравнение по времени done
        carriage_node = carriage_node->next;
    }
}

void check_ranks_and_merge(binomial_heap* binom_heap){
    binomial_node* tmp = binom_heap->last_node;
    binomial_node* next_copy = NULL;
    while ((tmp != NULL) && (tmp->next != NULL)){
        if (tmp->rank == tmp->next->rank) {
            if (tmp->priority < tmp->next->priority) {
                next_copy = tmp->next;
                if (tmp == binom_heap->last_node) {
                    binom_heap->last_node = next_copy;
                }
                merge_binomial_nodes(tmp->next, tmp);
                tmp = next_copy;
            }
            else if (tmp->priority == tmp->next->priority){
               if (tmp->date_time <= tmp->next->date_time){
                   merge_binomial_nodes(tmp,tmp->next);
               }
               else{
                   next_copy = tmp->next;
                   merge_binomial_nodes(tmp->next,tmp);
                   if (tmp == binom_heap->last_node) {
                       binom_heap->last_node = next_copy;
                   }
                   tmp = next_copy;
               }
            } //нужно добавить сравнения времени. done

            else {
                merge_binomial_nodes(tmp, tmp->next);
            }

        }
        else{
            tmp = tmp->next;
        }

    }


}

void add_elem_to_binomial_heap(unsigned int priority,time_t date_time,unsigned int appln_id, char* application_text,binomial_heap* binom_heap) {
    binomial_node* node = (binomial_node*)malloc(sizeof(binomial_node));
    if (node == NULL) {
        memory_error();
    }
    node->next = NULL;
    node->previous = NULL;
    node->priority = priority;
    node->rank = 0;
    node->sons = NULL;
    node->date_time = date_time;
    node->application_id = appln_id;
    node->application_text = (char*)malloc(sizeof(char)*(strlen(application_text)+1));
    if (node->application_text == NULL){
        return memory_error();
    }
    strcpy(node->application_text,application_text);
    if (binom_heap->last_node == NULL) {
        binom_heap->last_node = node;
        binom_heap->last_node->next = NULL;
        binom_heap->last_node->previous = NULL;
        binom_heap->max = binom_heap->last_node;
        return;
    }
    if ((node->priority) > (binom_heap->max->priority)){
        binom_heap->max=node;
    }
    else if (node->priority == binom_heap->max->priority){
        if (node->date_time <= binom_heap->max->date_time){
            binom_heap->max = node;
        }
    }
// cюда добавить при одинаковых значениях сравнивать время  done
    binom_heap->last_node->previous = node;
    node->next = binom_heap->last_node;
    node->previous = NULL;
    binom_heap->last_node = node;
    check_ranks_and_merge(binom_heap);



}
void add_elem_to_binomial_heap_interface(unsigned int priority,time_t date_time, unsigned int appln_id, char* application_text,void* binom_heap){
    add_elem_to_binomial_heap(priority,date_time,appln_id,application_text,(binomial_heap*)binom_heap);
}
void merge_binomial_heaps_inside(binomial_heap* binom_heap, binomial_node* node2){
    if (binom_heap->last_node == NULL){
        binom_heap->last_node = node2;
        return;
    }
    binomial_node* tmp1 = binom_heap->last_node;
    binomial_node* tmp2 = node2;
    binomial_node* tmp_copy1 = NULL;
    binomial_node* tmp_copy2 = NULL;
    binomial_node* tmp_next = NULL;
    while((tmp1 != NULL) && (tmp2 != NULL)){
        tmp_next = tmp2->next;
        if (tmp1->rank == tmp2->rank) {
            if (tmp1->priority > tmp2->priority) {
                tmp2->previous = NULL;
                tmp2->next = NULL;
                merge_binomial_nodes(tmp1, tmp2);
                if (tmp1->next == NULL) {
                    if (tmp_next != NULL) {
                        tmp_next->previous = tmp1;
                    }
                    tmp1->next = tmp_next;
                    break;
                }
                tmp1 = tmp1->next;
            }// сравнение по времени
            else if (tmp1->priority == tmp2->priority) {
                if (tmp1->date_time <= tmp2->date_time) {
                    tmp2->next = NULL;
                    tmp2->previous = NULL;
                    merge_binomial_nodes(tmp1, tmp2);
                    if (tmp1->next == NULL) {
                        if (tmp_next != NULL) {
                            tmp_next->previous = tmp1;
                        }
                        tmp1->next = tmp_next;
                        break;
                    }
                    tmp1 = tmp1->next;
                } else {
                    tmp2->previous = tmp1->previous;
                    if (tmp1->previous != NULL) {
                        tmp1->previous->next = tmp2;
                    }
                    tmp2->next = tmp1->next;
                    if (tmp1->next != NULL) {
                        tmp1->next->previous = tmp2;
                    }
                    tmp1->previous = NULL;
                    tmp1->next = NULL;
                    merge_binomial_nodes(tmp2, tmp1);
                    if (tmp1 == binom_heap->last_node) {
                        binom_heap->last_node = tmp2;
                    }
                    tmp1 = tmp2->next;
                    if (tmp2->next == NULL) {
                        tmp2->next = tmp_next;
                        break;
                    }
                }

            } else {
                tmp2->previous = tmp1->previous;
                if (tmp1->previous != NULL) {
                    tmp1->previous->next = tmp2;
                }
                tmp2->next = tmp1->next;
                if (tmp1->next != NULL) {
                    tmp1->next->previous = tmp2;
                }
                tmp1->previous = NULL;
                tmp1->next = NULL;
                merge_binomial_nodes(tmp2, tmp1);
//                if (tmp1 == binom_heap->max){
//                    binom_heap->max = tmp2;
//                }
                if (tmp1 == binom_heap->last_node) {
                    binom_heap->last_node = tmp2;
                }
                tmp1 = tmp2->next;
                if (tmp2->next == NULL) {
                    tmp2->next = tmp_next;
                    break;
                }
            }
        }
        else {
            tmp_copy1 = tmp1->previous;
            tmp1->previous = tmp2;
            tmp2->next = tmp1;
            tmp2->previous = tmp_copy1;
            if (tmp_copy1 == NULL){
                binom_heap->last_node = tmp2;
            }
            else{
                tmp_copy1->next = tmp2;
            }
        }
        tmp2 = tmp_next;
    }

}
void merge_binomial_heaps(binomial_heap* heap1, binomial_heap* heap2){
    merge_binomial_heaps_inside(heap1,heap2->last_node);
}
void merge_binomial_heaps_interfae(void* heap1, void* heap2){
    merge_binomial_heaps((binomial_heap*)heap1, (binomial_heap*)heap2);
}
void remove_elem_from_binomial_heap(binomial_heap* binom_heap,binomial_node* node){
    if (node == NULL){
        return ;
    }
    if (node->previous != NULL) {
        node->previous->next = node->next;
    }
    if (node->next != NULL) {
        node->next->previous = node->previous;
    }
    if (node == binom_heap->last_node){
        binom_heap->last_node = binom_heap->last_node->next;
    }
    binomial_node* tmp = NULL;
    if (node->sons != NULL) {
        tmp = node->sons;
        while (tmp->previous != NULL) {
            tmp = tmp->previous;
        }
        merge_binomial_heaps_inside(binom_heap, tmp);
    }
    binom_heap->max = binom_heap->last_node;
    set_min_in_binom_heap(binom_heap);
    free(node->application_text);
    free(node);
    node = NULL;
    check_ranks_and_merge(binom_heap);
}
void remove_binomial_heap_max(binomial_heap* heap){
    remove_elem_from_binomial_heap(heap,heap->max);
}
void delete_binomial_heap(binomial_heap* binom_heap){
    while(binom_heap->last_node != NULL) {
        printf("%u %u\n", binom_heap->max->priority,binom_heap->max->date_time);
        remove_elem_from_binomial_heap(binom_heap, binom_heap->max);
    }
    free(binom_heap);
}

fibonacci_heap* create_fibonacci_heap() {
    fibonacci_heap *heap = (fibonacci_heap *) malloc(sizeof(fibonacci_heap));
    if (heap == NULL){
        memory_error();
    }
    heap->max = NULL;
    heap->last_node = NULL;
    return heap;
}



void add_elem_to_fibonacci_heap(unsigned int priority, time_t date_time, unsigned int appln_id ,char* application_text, fibonacci_heap* heap){
    fibonacci_node* node = (fibonacci_node*)malloc(sizeof(fibonacci_node));
    if (node == NULL){
        memory_error();
    }
    node->application_text = (char*)malloc(sizeof(char)*(strlen(application_text)+1));
    if (node->application_text == NULL){
        memory_error();
    }
    strcpy(node->application_text,application_text);
    node->priority = priority;
    node->date_time = date_time;
    node->sons = NULL;
    node->next = NULL;
    node->rank = 0;
    node->application_id = appln_id;
    if (heap->last_node == NULL){
        node->previous = NULL;
        heap->last_node = node;
        heap->max = node;
        return ;
    }
    if (node->priority > heap->max->priority){
        heap->max = node;
    }
    else if (node->priority == heap->max->priority){
        if (node->date_time <= heap->max->date_time){
            heap->max = node;
        }
    }
    heap->last_node->next = node;
    node->previous = heap->last_node;
    heap->last_node = node;
}

//
//void add_elem_to_fibonacci_heap(unsigned int priority, time_t date_time,unsigned int dep_num, unsigned int appln_id, char* application_text, fibonacci_heap* heap){
//    add_elem_to_fibonacci_heap_strct(priority,date_time,application_text,0,heap);
//}



void set_max_in_fibonacci_heap(fibonacci_heap* heap){
    fibonacci_node* tmp = heap->last_node;
    while (tmp != NULL){
        if (tmp->priority > heap->max->priority){
            heap->max = tmp;
        }
        else if (tmp->priority == heap->max->priority){
            if (tmp->date_time < heap->max->date_time){
                heap->max = tmp;
            }
        }
        tmp = tmp->previous;
    }
}
unsigned int merge_fibonacci_nodes(fibonacci_node* node1, fibonacci_node* node2,fibonacci_node** buff){
//    printf("merge");
    unsigned int last_index;
    fibonacci_node* tmp = NULL;
    if (node1->priority < node2->priority){
        tmp = node1;
        node1 = node2;
        node2 = tmp;
    }
    else if (node1->priority == node2->priority){
        if (node1->date_time > node2->date_time){
            tmp = node1;
            node1 = node2;
            node2 = tmp;
        }

    }
    node1->rank++;
    if (node1->sons == NULL){
        node1->sons = node2;
//        node1->sons->previous = NULL;
//        node1->sons->next = NULL;
    }
    else{
        tmp = node1->sons;
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = node2;
        node2->previous = tmp;
        node2->next = NULL;
    }
    buff[node1->rank-1] = NULL;
//    node1->next = NULL;
//    node1->previous = NULL;
    if (buff[node1->rank] != NULL){
        return merge_fibonacci_nodes(node1,buff[node1->rank],buff);
    }
    else{
        buff[node1->rank] = node1;
        last_index = node1->rank;
        return last_index;
    }
}
void remove_elem_from_fibonacci_heap(fibonacci_node* node,fibonacci_heap* heap){
    if (node == NULL){
        return;
    }
    int size = 100;
    fibonacci_node* carriage_node;
    fibonacci_node** buff = (fibonacci_node**)malloc(sizeof(fibonacci_node*)*size);
    if (buff == NULL){
        return memory_error();
    }
    for (int i = 0; i < size; i++){
        buff[i] = NULL;
    }
    if (node->previous != NULL){
        node->previous->next = node->next;
    }
    if (node->next != NULL){
        node->next->previous = node->previous;
    }
    else{
        heap->last_node = heap->last_node->previous;
    }
    if (node->sons != NULL){
        node->sons->previous = heap->last_node;
        if (heap->last_node != NULL) {
            heap->last_node->next = node->sons;
        }
        carriage_node = node->sons;
        while (carriage_node->next != NULL){
            carriage_node = carriage_node->next;
        }
        heap->last_node = carriage_node;
    }
    unsigned int last_index = 0;
    fibonacci_node* node_from_array;
    carriage_node = heap->last_node;
    fibonacci_node* tmp_previous;
    fibonacci_node** tmp_for_realloc;
    unsigned int last_index_tmp;
    while(carriage_node != NULL){
        if (carriage_node->rank > size - 2){
            size *= 2;
            tmp_for_realloc = (fibonacci_node**) realloc(buff,sizeof(fibonacci_node*)*size);
            if (tmp_for_realloc == NULL){
                memory_error();
            }
            buff = tmp_for_realloc;
            tmp_for_realloc = NULL;
        }
        tmp_previous = carriage_node->previous;
        carriage_node->next = NULL;
        carriage_node->previous = NULL;
        if ((node_from_array = buff[carriage_node->rank]) != NULL){
            last_index_tmp = merge_fibonacci_nodes(node_from_array,carriage_node,buff);
            if (last_index_tmp > last_index){
                last_index = last_index_tmp;
            }
        }
        else{
            if (last_index < carriage_node->rank) {
                last_index = carriage_node->rank;
            }
//            carriage_node->next = NULL;
//            carriage_node->previous = NULL;
            buff[carriage_node->rank] = carriage_node;
        }
        carriage_node = tmp_previous;
    }
    heap->last_node = buff[last_index];
//    heap->last_node->next = NULL;
//    heap->last_node->previous = NULL;
    carriage_node = heap->last_node;
    if (last_index != 0) {
        unsigned int i = last_index - 1;
        while (1) {
//            printf("while");
            if (buff[i] != NULL) {
                carriage_node->previous = buff[i];
                buff[i]->next = carriage_node;
                buff[i]->previous = NULL;
                carriage_node = buff[i];
            }
            if (i == 0) {
                break;
            }
            i--;
        }
    }
    heap->max = heap->last_node;
    set_max_in_fibonacci_heap( heap);
    free(node->application_text);
    node->application_text = NULL;
    free(node);
    node = NULL;
    free(buff);
}
fibonacci_node* get_fibonacci_max(fibonacci_heap* heap){
    return heap->max;
}
void remove_fibonacci_max(fibonacci_heap* heap){
    remove_elem_from_fibonacci_heap(heap->max,heap);
}
void delete_fibonacci_heap(fibonacci_heap* heap){
    fibonacci_node* tmp = heap->last_node;
    while(heap->last_node != NULL){
        printf("%u %u\n",heap->max->priority,heap->max->date_time);
        remove_elem_from_fibonacci_heap(heap->max,heap);
    }
    free(heap);
    heap = NULL;
}

void merge_fibonacci_heaps(fibonacci_heap* heap1, fibonacci_heap* heap2){
    fibonacci_node* first_node_of_heap2 = heap2->last_node;
    while (first_node_of_heap2->previous != NULL){
        first_node_of_heap2 = first_node_of_heap2->previous;
    }
    heap1->last_node->next = first_node_of_heap2;
    first_node_of_heap2->previous = heap1->last_node;
    heap1->last_node = heap2->last_node;
}



leftist_heap* create_leftist_heap(){
    leftist_heap* heap = (leftist_heap*)malloc(sizeof(leftist_heap));
    if (heap == NULL){
        memory_error();
    }
    heap->root = NULL;
    return heap;
}

leftist_node* merge_leftist_heaps_inside(leftist_node** node1, leftist_node** node2) { // что если будет ситуация merge узла и end
    if (*node1 == NULL){
        return  *node2;
    }
    else if (*node2 == NULL){
        return *node1;
    }
    leftist_node* tmp = NULL;
    if ((*node1)->priority < (*node2)->priority){
        tmp = *node1;
        *node1 = *node2;
        *node2 = tmp;

    }
    else if ((*node1)->priority == (*node2)->priority){
        if ((*node1)->date_time > (*node2)->date_time){
            tmp = *node1;
            *node1 = *node2;
            *node2 = tmp;
        }
    }
    (*node1)->right = merge_leftist_heaps_inside(&((*node1)->right),node2);
    (*node1)->npl = (*node1)->right->npl +1;
//    leftist_node* tmp2 = NULL;
    if ((*node1)->left == NULL){
        tmp = (*node1)->right;
        (*node1)->right = NULL;
        (*node1)->left = tmp;
        (*node1)->npl = 0;
    }
    else if ((*node1)->right->npl > (*node1)-> left->npl){
        tmp = (*node1)->right;
        (*node1)->right = (*node1)->left;
        (*node1)->left = tmp;
        (*node1)->npl = (*node1)->right->npl + 1;
    }
    return *node1;

}
void merge_leftist_heaps(leftist_heap* heap1, leftist_heap* heap2){
    heap1->root = merge_leftist_heaps_inside((&heap1->root),(&heap2->root));
}
void add_elem_to_leftist_heap(unsigned int priority, time_t date_time,unsigned int appln_id ,char* application_text,leftist_heap* heap){
    leftist_node* node = (leftist_node*)malloc(sizeof(leftist_node));
    if ((node == NULL)){
        memory_error();
    }
    node->application_text = (char*)malloc(sizeof(char)*(strlen(application_text)+1));
    if (node->application_text == NULL){
        memory_error();
    }
    node->priority = priority;
    node->date_time = date_time;
    node->left = NULL; //heap->end;
    node->right = NULL; //heap->end;
    node->application_id = appln_id;
    node->npl = 0;
    strcpy(node->application_text,application_text);
    if (heap->root == NULL){
        heap->root = node;
        return;
    }
    merge_leftist_heaps_inside(&(heap->root),&node);
}

void remove_leftist_max(leftist_heap* heap){
    if (heap->root == NULL){
        return;
    }
    leftist_node* node_to_delete = heap->root;
    leftist_node** left = &(heap->root->left);
    leftist_node** right = &(heap->root->right);
    heap->root = merge_leftist_heaps_inside(left,right);
    free(node_to_delete->application_text);
    free(node_to_delete);
}

void delete_leftist_heap(leftist_heap** heap){
    while((*heap)->root != NULL){
        printf("%u %u\n",(*heap)->root->priority,(*heap)->root->date_time);
        remove_leftist_max(*heap);
    }
    free(*heap);
}




skew_heap* create_skew_heap(){
    skew_heap* heap = (skew_heap*)malloc(sizeof(skew_heap));
    if (heap == NULL){
        memory_error();
    }
    heap->root = NULL;
    return heap;
}

void merge_skew_heaps_inside(skew_node** node1, skew_node** node2){
    if (((*node1) == NULL) || ((*node2) == NULL)){
        return;
    }
    skew_node* tmp = NULL;
    if ((*node1)->priority < (*node2)->priority){
        tmp = *node1;
        *node1 = *node2;
        *node2 = tmp;

    }
    else if ((*node1)->priority == (*node2)->priority){
        if ((*node1)->date_time > (*node2)->date_time){
            tmp = *node1;
            *node1 = *node2;
            *node2 = tmp;
        }
    }
    else {
        tmp = (*node1)->right;
        (*node1)->right = (*node1)->left;
        (*node1)->left = tmp;
    }
    if ((*node1)->left == NULL){
        (*node1)->left = *node2;
        return;
    }
    else {
        merge_skew_heaps_inside(&((*node1)->left),node2);
    }
}
void merge_skew_heaps(skew_heap* heap1, skew_heap* heap2){
    merge_skew_heaps_inside(&heap1->root,&heap2->root);
}
void add_elem_to_skew_heap(unsigned int priority,time_t date_time, unsigned int appln_id,char* application_text,skew_heap* heap){
    skew_node* node = (skew_node*)malloc(sizeof(skew_node));
    if (node == NULL){
        memory_error();
    }
    node->right = NULL;
    node->left = NULL;
    node->priority = priority;
    node->date_time = date_time;
    node->application_id = appln_id;
    node->application_text = (char*)malloc(sizeof(char)*(strlen(application_text)+1));
    if (node->application_text == NULL){
        memory_error();
    }
    strcpy(node->application_text,application_text);
    if (heap->root == NULL){
        heap->root = node;
        return;
    }
    merge_skew_heaps_inside(&(heap->root),&(node));
}

void remove_skew_max(skew_heap* heap){
    if (heap->root == NULL){
        return;
    }
    skew_node* node_to_delete = heap->root;
    skew_node** left = &(heap->root->left);
    skew_node** right = &(heap->root->right);
    merge_skew_heaps_inside(left,right);
    heap->root = *left;
    free(node_to_delete->application_text);
    free(node_to_delete);
}
void delete_skew_heap(skew_heap** heap){
    while ((*heap)->root != NULL){
        printf("%u %u\n",(*heap)->root->priority,(*heap)->root->date_time);
        remove_skew_max(*heap);
    }
    free(*heap);
}





treap_heap* create_treap_heap(){
    treap_heap* heap = (treap_heap*)malloc(sizeof(treap_heap));
    if (heap == NULL){
        memory_error();
    }
    heap->root = NULL;
    return heap;
}

void split_treap_heap(treap_node* root,time_t date_time_key,treap_node** node1,treap_node** node2){
        if (root == NULL){
            *node1 = NULL;
            *node2 = NULL;
            return;
        }
        if (root->date_time < date_time_key){
            split_treap_heap(root->right,date_time_key,&(root->right),node2);
            *node1 = root;
        }
        else{
            split_treap_heap(root->left,date_time_key,node1,&(root->left));
            *node2 = root;
        }
}
treap_node* merge_treap_heap_inside(treap_node* node1, treap_node* node2){
    if (node1  == NULL){
        return node2;
    }
    else if (node2 == NULL){
        return node1;
    }
    if (node1->priority > node2->priority){
        node1->right = merge_treap_heap_inside(node1->right,node2);
        return node1;
    }
    else if (node1->priority == node2->priority){
        if (node1->date_time <= node2->date_time){
            node1->right = merge_treap_heap_inside(node1->right,node2);
            return node1;
        }
    }
    else{
        node2->left = merge_treap_heap_inside(node1,node2->left);
        return  node2;
    }
}
void merge_treap_heaps(treap_heap* heap1, treap_heap* heap2){
    merge_treap_heap_inside(heap1->root,heap2->root);
}
void add_elem_to_treap_heap(unsigned int priority, time_t date_time, unsigned int appln_id ,char* application_text, treap_heap* heap){
    treap_node* node = (treap_node*)malloc(sizeof(treap_node));
    if (node == NULL){
        memory_error();
    }
    node->application_text = (char*)malloc(sizeof(char)*(strlen(application_text)+1));
    strcpy(node->application_text,application_text);
    node->priority = priority;
    node->date_time = date_time;
    node->right = NULL;
    node->left = NULL;
    node->application_id = appln_id;
    if (heap->root == NULL){
        heap->root = node;
        return;
    }
    treap_node* root1 = NULL;
    treap_node* root2 = NULL;
    split_treap_heap(heap->root,date_time,&root1,&root2);
    root1 = merge_treap_heap_inside(root1,node);
    heap->root = merge_treap_heap_inside(root1,root2);
}

void remove_treap_max(treap_heap* heap){
    treap_node* node_to_delete = heap->root;
    heap->root = merge_treap_heap_inside(heap->root->left,heap->root->right);
    free(node_to_delete->application_text);
    node_to_delete->application_text = NULL;
    free(node_to_delete);
    node_to_delete = NULL;
}
void delete_treap_heap(treap_heap* heap){
    while(heap->root != NULL){
        printf("%u  %u\n",heap->root->priority, heap->root->date_time);
        remove_treap_max(heap);
    }
    free(heap);
}


hash_table* create_hash_table() {
    hash_table* table = (hash_table*)malloc(sizeof(hash_table));
    if (table == NULL){
        memory_error();
    }
    table->size = 25;
    table->current_size = 0;
    table->array = (hash_table_node*)malloc(sizeof(hash_table_node)*table->size);
    table->dep_quantity = 0;
    if (table->array == NULL){
        free(table);
        memory_error();
    }
    for (int i = 0; i < table->size; i++){
        table->array[i].next = NULL;
        table->array[i].ptr = NULL;
    }
    return table;
}
unsigned int hash(unsigned int key){
    return key%100;
}

void insert_into_hash_table(unsigned int key, void* ptr,hash_table** table){
    unsigned int index = hash(key);
    hash_table* tmp_table = NULL;
    if (index >= (*table)->size){
        (*table)->size += 25;
        tmp_table = (hash_table*)realloc(table,sizeof(hash_table)*(*table)->size);
        if (tmp_table == NULL){
            memory_error();
        }
        *table = tmp_table;
    }
    hash_table_node* tmp = NULL;
    if ((*table)->array[index].ptr == NULL){
        (*table)->array[index].ptr = ptr;
        (*table)->array[index].department_number = key;
    }
    else{
        tmp = &(*table)->array[index];
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = (hash_table_node*)malloc(sizeof(hash_table_node));
        if (tmp->next == NULL){
            memory_error();
        }
        tmp = tmp->next;
        tmp->next = NULL;
        tmp->department_number = key;
        tmp->ptr = ptr;
    }
}
void insert_into_hash_table_interface(unsigned int key,void* ptr,void** table){
    insert_into_hash_table(key,ptr,(hash_table**)table);
}
void* get_from_hash_table(unsigned int key,hash_table* table) {
    if (table == NULL) {
        return NULL;
    }
    else if (table->array == NULL){
        return NULL;
    }
    unsigned int i = hash(key);
    hash_table_node* tmp = &table->array[i];
    while(tmp != NULL) {
        if (tmp->department_number == key) {
            return tmp;
        } else {
            tmp = tmp->next;
        }
    }
    return NULL;
}
void* get_from_hash_table_interface(unsigned int key,void* table){
    return get_from_hash_table(key,(hash_table*)table);
}
void* get_heap_from_hash_table_node(hash_table_node* node){
    return node->ptr;
}
void* get_heap_from_hash_table_node_interface(void* node){
    return get_heap_from_hash_table_node((hash_table_node*)node);
}


void delete_hash_table(hash_table* table){
    if (table == NULL) {
        return;
    } else if (table->array == NULL) {
        return;
    }

    hash_table_node *tmp;
    hash_table_node *tmp_next;
    for (int i = 0; i < table->size; i++) {
        tmp = &table->array[i];
        while (tmp->next != NULL) {
            tmp_next = tmp->next;
            free(tmp);
            tmp = tmp_next;
        }
    }
}

//unsigned int get_acceptable_number_hash_node(hash_table_node* node){
//    return node->acceptable_quantity_applications;
//}
//unsigned int get_acceptable_number_hash_node_interface(void* node){
//    return get_acceptable_number_hash_node((hash_table_node*)node);
//}

departments* create_departments(departments_option* dep_ops){
    departments* dep = (departments*)malloc(sizeof(departments));
    unsigned int acceptable_number;
    if (dep == NULL){
        memory_error();
    }
    dep->time_we_have = dep_ops->end_date_time - dep_ops->start_date_time;
    dep->current_time = dep_ops->start_date_time;
    dep->options = dep_ops;
    dep->heap_context = (heap_context*)malloc(sizeof(heap_context));
    dep->struct_context = (struct_to_save_heaps_context*)malloc(sizeof(struct_to_save_heaps_context));
    dep->applications_quantity = (unsigned int*)malloc(sizeof(unsigned int)*dep_ops->departments_quantity);
    dep->departments_number = (unsigned int*)malloc(sizeof(unsigned int)*dep_ops->departments_quantity);
    dep->departments_capacity = (unsigned int*)malloc(sizeof(unsigned int)*dep_ops->departments_quantity);
    dep->all_applications = create_fibonacci_heap();
    if ((dep->heap_context == NULL) || (dep->all_applications == NULL) ||(dep->struct_context == NULL) || (dep->applications_quantity == NULL) || (dep->departments_number == NULL) || (dep->departments_capacity == NULL)){
        memory_error();
    }
    dep->struct_context->strct = NULL;
    dep->struct_context->insert = NULL;
    dep->heap_context->create_heap = NULL;
    dep->heap_context->add_elem_to_heap = NULL;
//    dep->structure_for_heaps; // сделать для хеша и тд
    switch(heap_type_recog(dep_ops)){
        case BinaryHeap:
            dep->heap_context->create_heap = create_binary_heap_interface;
            dep->heap_context->add_elem_to_heap = add_elem_to_binary_heap_interface;
            break;
    }
    switch(data_type_recog(dep_ops)){
        case HashSet:
            dep->struct_context->strct = create_hash_table();
            ((hash_table*)(dep->struct_context->strct))->dep_quantity = dep_ops->departments_quantity;
            dep->struct_context->insert = insert_into_hash_table_interface;
            dep->struct_context->get_heap = get_from_hash_table_interface;
            break;
        case DynamicArray:
            break;
        case BinarySearchTree:
            break;
        case Trie:
            break;
    }
//    unsigned int department_number = rand();
    unsigned int hash_num = 0;
    unsigned int department_number = 1;
    for (int i = 0; i < dep_ops->departments_quantity; i++){
        department_number++;
        dep->departments_number[i] = department_number;
        hash_num = hash(department_number);
        dep->departments_capacity[hash_num] = dep_ops->overload_coefficient*dep_ops->operators_quantity[i];
        dep->applications_quantity[hash_num] = 0;
        dep->struct_context->insert(department_number,dep->heap_context->create_heap(),&(dep->struct_context->strct));
        //TODO рассчитать количество разрешенных сообщений в зависимости от кол-во операторов
    }
    return dep;
}
int check_overload(unsigned int dep_num,departments* deps){
    unsigned int hash_num = hash(dep_num);
    if (deps->applications_quantity[hash_num] == deps->departments_capacity[hash_num]){
        return 1;
    }
    return 0;
}
//void create_application(application* apl,struct tm* tm_struct,FILE* file) {
//    char* inf = (char*)malloc(sizeof(char)*20);create_bina
//    parse_time(file,tm_struct);
//    time_t date_time = mktime(tm_struct);
//    apl->date_time = date_time;
//    fscanf(file,"%d",&apl->priority);
//    fscanf(file,"%d",)
//}
void write_application_text(FILE* file, char** text,int* size) {
    char* tmp;
    char letter;
    int i = 0;
    while (((letter = fgetc(file)) != EOF) && ((letter = fgetc(file)) != '\n')){
        if (i == *size-1){
            *size += 10;
            tmp = realloc(*text,sizeof(char)*(*size));
            if (tmp == NULL) {
                memory_error();
            }
            *text = tmp;
        }
        (*text)[i] = letter;
        i++;
    }
    (*text)[i] = '\n';
}
void add_applications_to_departments(departments* dep,char** file_with_applications,int file_count) {
    time_t apl_date_time;
    unsigned int priority = 0;
    unsigned int department_number = 0;
    int size = 10;
    struct tm* time_info;
    char date_time[21];
    char *application_text = (char *) malloc(sizeof(char) * size);
    FILE *file;
    struct tm *tm_struct = (struct tm *) malloc(sizeof(struct tm));
    FILE* log_file = fopen("log_file.txt","w");
    if ((tm_struct == NULL) || (application_text == NULL)) {
        memory_error();
    }
    unsigned int application_id_count = 0;
    void* heap = NULL;
    int i = 3;
    while (i < file_count) {
        file = fopen(file_with_applications[i], "r");
        while (1) {
            application_id_count++;
            parse_time(file, tm_struct);
            apl_date_time = mktime(tm_struct);
            if ((apl_date_time >= dep->options->start_date_time) && (apl_date_time <= dep->options->end_date_time)) {
                fscanf(file, "%u", &priority);
                if (priority < dep->options->max_priority) {
                    fscanf(file, "%u", &department_number);
                    if ((heap = dep->struct_context->get_heap(department_number, dep->struct_context->strct)) != NULL) {
                        time_info = localtime(&dep->current_time);
                        strftime(date_time,sizeof(date_time),"%Y-%m-%d %H:%M:%S",time_info);
                        if (!check_overload(department_number,dep)){
                            write_application_text(file, &application_text, &size);
                            fprintf(log_file,"%s NEW_REQUEST application №%u was received by department №%u",date_time,application_id_count,department_number);
                            dep->heap_context->add_elem_to_heap(priority,apl_date_time,application_id_count,application_text,heap);
                        }
                        else{
                            for (int t = 0; t < dep->options->departments_quantity;t++){
                                if(!check_overload(dep->departments_number[i],dep)){
                                    dep->applications_quantity[hash(dep->departments_number[t])]++;
                                    heap = dep->struct_context->get_heap(dep->departments_number[t],dep->struct_context->strct);
                                    dep->heap_context->add_elem_to_heap(priority,apl_date_time,application_id_count,application_text,heap);
                                    fprintf(log_file,"%s DEPARTMENT_OVERLOADED application №%u was received by department №%u and overloaded, application was sent to department №%u",date_time,application_id_count,department_number,dep->departments_number[i]);

                                }
                            }
                        }
                    }
                }
            }
            if (fgetc(file) == EOF) {
                break;
            }
        }
        i++;
        fclose(file);
    }
}

//void start_work(departments* dep){
//    unsigned int number;
//    void* heap = NULL;
//    fibonacci_node* node = NULL;
//    void* struct_node = NULL;
//    while (dep->all_applications->last_node != NULL) {
//        node = get_fibonacci_max(dep->all_applications);
//        struct_node = dep->struct_context->get_struct_node(node->dep_number,dep->struct_context->strct);
//         if (!dep->struct_context->check_overload(struct_node)){
//             heap = get_heap_from_hash_table_node_interface(struct_node);
//             dep->struct_context->insert()
//         }
//         else{
//             //TODO логи логи сука логи
//         }
//        if (dep->departments_capacity[hash(node->dep_number,dep->options->departments_quantity)]) //TODO думаю пока добавить счетчики  в hash node чтобы не вычислять по массиву каждый раз
//        dep->heap_context->add_elem_to_heap(node->priority,node->date_time,node->application_text,heap);
//        remove_fibonacci_max(dep->all_applications);
//    }
//}

