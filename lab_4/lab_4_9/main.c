#include"func.h"

//typedef int tkey;
//typedef void *tvalue;
//
//typedef struct heap1 {} heap1;
//typedef struct heap2 {} heap2;
//
//typedef struct collection1 {} collection1;
//typedef struct collection2 {} collection2;
//
//void insert_heap1(void *heap, tkey key, tvalue value)
//{
//    heap1 *h = (heap1 *)heap;
//    // TODO
//}
//
//void insert_heap2(void *heap, tkey key, tvalue value)
//{
//    heap2 *h = (heap2 *)heap;
//    // TODO
//}
//
//void* add_value;
//
//typedef struct heap_context {
//    void *data;
//    void (*insert)(void*, tkey, tvalue) //(void (*)(void *, tkey, tvalue))(add_value);
//    int elem = (int)floatttt;
//}heap_context;
//
//    heap_context hc;
//    hc.data = malloc(sizeof(heap1));
//hc.insert = insert_heap1;

//
//    double elen = 7.0L;
//    int elen2 = (int)elen;
//
//    void* ptr;
//
//    int (*get_funs)(int, double) = (int(*)(int, double))ptr;
//
//    return 0;

void print_dep_ops(departments_option * dep){
    printf("%s\n",dep->heap_type);
    printf("%s\n",dep->data_type);
    printf("%u\n",dep->min_processing_time);
    printf("%u\n",dep->max_processing_time);
    printf("%lu\n",dep->start_date_time);
    printf("%lu\n",dep->end_date_time);
    printf("%f\n",dep->overload_coefficient);

}


int main(int argc, char** argv) {
    char *end;
    int status = 0;
    char buff_str[20];
    FILE *file1;
    if (argc < 2) {
        printf("Enter files\n");
        return 0;
    }
    unsigned int MAX_PRIORITY;
    if (str_to_unsigned_int(argv[1],&MAX_PRIORITY)){
        printf("You enter not a number or too big number");
        return 0;
    }
    else if (MAX_PRIORITY == 0) {
        printf("Max priority can't be 0\n");
        return 0;
    } else if (check_files(argc, argv)) {
        printf("Check the files names\n");
        return 0;
    }
    file1 = fopen(argv[2], "r");
    departments_option* deps_option;
    create_departments_option(&deps_option,file1);
    deps_option->max_priority = MAX_PRIORITY;
    print_dep_ops(deps_option);
    departments* dep = create_departments(deps_option);
//    add_applications_to_departments(dep,argv,argc);
    start_work(dep,argc,argv);
//print ((hash_table_node*)((hash_table*)(dep->struct_context->strct))->array)[2]
//    print ((binary_heap*)(((hash_table_node*)(((hash_table*)(dep->struct_context->strct))->array))[2].ptr))->heap->application_text
}