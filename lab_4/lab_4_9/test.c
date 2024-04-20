#include"func.h"
//  cmake -DCMAKE_BUILD_TYPE=Debug ..
void print_b_heap(binary_heap* heap){
    for(int i = 0; i <= heap->current_size; i++){
        printf("%u %u\n",heap->heap[i].priority,heap->heap[i].date_time);
    }
}
int main(){
    unsigned int number = 0;
    int size = 10;
    char* end;
    time_t date_time;
    printf("----------------------------------------------------------------------------------\n");
    printf("binary heap\n");
    binary_heap* binary_heap1 = create_binary_heap();
    FILE* binary_heap_file = fopen("binary_test.txt","r");
    if (binary_heap_file == NULL){
        printf("file not found\n");
    }
    char letter[10];
    printf("test\n");
    while (fscanf(binary_heap_file,"%s",letter) != EOF){
        number = strtoul(letter,&end,10);
        date_time = rand()%100;
        add_elem_to_binary_heap(number,date_time,"test\0",binary_heap1);

    }
    print_b_heap(binary_heap1);
    printf("----------------------------------------------------------------------------------\n");
    printf("binary heap2\n");
    binary_heap* binary_heap2 = create_binary_heap(size);
    FILE* binary_heap_file2 = fopen("binary_test2.txt", "r");
    while ((fscanf(binary_heap_file2,"%s",letter)) != EOF){
        number = strtoul(letter,&end,10);
        date_time = rand()%100;
        add_elem_to_binary_heap(number,date_time,"test\0",binary_heap2);
    }
    print_b_heap(binary_heap2);
    printf("----------------------------------------------------------------------------------\n");
    printf("merge binomial_heap and binary_heap2\n");
    merge_binary_heaps(binary_heap1,binary_heap2);
    print_b_heap(binary_heap1);
    delete_binary_heap(&binary_heap1);
    delete_binary_heap(&binary_heap2);
    printf("----------------------------------------------------------------------------------\n");
    printf("binomial_heap\n");
    FILE* binomial_heap_file = fopen("binomial_test.txt", "r");
    binomial_heap* binomial_heap = create_binomial_heap();
     while ((fscanf(binomial_heap_file,"%s",letter)) != EOF){
         number = strtoul(letter,&end,10);
         date_time = rand()%100;
        add_elem_to_binomial_heap(number,date_time,"test",binomial_heap);

    }
    delete_binomial_heap(binomial_heap);
    binomial_heap = NULL;
    printf("----------------------------------------------------------------------------------\n");
    printf("Fibonacci heap\n");
    FILE* fibonacci_heap_file = fopen("fibonacci_test.txt","r");
    fibonacci_heap* fibonacci_heap = create_fibonacci_heap();
    while (fscanf(fibonacci_heap_file,"%s",letter) != EOF){
        number = strtoul(letter,&end,10);
        date_time = rand()%100;
        add_elem_to_fibonacci_heap(number,date_time,"test_fib\n",fibonacci_heap);

    }
    delete_fibonacci_heap(fibonacci_heap);
    printf("----------------------------------------------------------------------------------\n");
    printf("Leftist heap\n");
    FILE* file_left = fopen("left_test.txt", "r");
    leftist_heap * leftist_heap = create_leftist_heap();
     while (fscanf(file_left,"%s",letter) != EOF){
        number = strtol(letter, &end, 10);
        date_time = rand() % 100;
        add_elem_to_leftist_heap(number, date_time, "test_left", leftist_heap);

     }




//11 23 17 15 19 13 21

    delete_leftist_heap(&leftist_heap);

    printf("----------------------------------------------------------------------------------\n");
    printf("Skewheap heap\n");
    FILE* file_skew = fopen("skew_test.txt", "r");
    skew_heap* skew_heap = create_skew_heap();
    while (fscanf(file_skew,"%s",letter) != EOF){
        number = strtol(letter, &end, 10);
        date_time = rand() % 100;
        add_elem_to_skew_heap(number, date_time, "test_left", skew_heap);

    }
    delete_skew_heap(&skew_heap);

    printf("----------------------------------------------------------------------------------\n");
    printf("Treap heap\n");
    treap_heap* treap_heap = create_treap_heap();
    FILE* file_treap = fopen("treap_test.txt","r");
    while (fscanf(file_treap,"%s",letter) != EOF){
        number = strtol(letter, &end, 10);
        date_time = rand() % 100;
        add_elem_to_treap_heap(number,date_time,"test_trip",treap_heap);
    }
//    delete_treap_heap(treap_heap);

    printf("----------------------------------------------------------------------------------\n");
    printf(" hash table with treap heap\n");
    hash_table* table = create_hash_table();
    insert_into_hash_table_interface(122,treap_heap,table);
    delete_treap_heap(table->array[22].ptr);



    return 0;
}


// проверить в биномиальной когда один узел ранга больше 1 * работает


