#include"func.h"
int ask_for_generating(){
    int answer = 0;
    while ((answer != 49) && (answer != 50)) {
        printf("Do you want to add parameters?\n1) Yes\n2) No\n");
        answer = getchar();
        while (getchar() != '\n'){};


    }
    return answer;
}
int compare_strings_array(char* str,int str_count, char array[][18]){
    for (int i = 0; i < str_count; i++){
         if (!strcmp(str,array[i])){
            return 1;
        }
    }
    return 0;
}
void construct_options(FILE* file){
    char* end;
    char heap_type[14];
    char struct_type[17];
    char heaps[6][18] = {"BinaryHeap","BinomialHeap","FibonacciHeap","SkewHeap","LeftistHeap","Treap"};
    char structs[4][18] = {"HashSet","DynamicArray","BinarySearchTree","Trie"};
    char buff[20] = "2030fadsf";
    int start_year;
    int end_year;
    while (!compare_strings_array(heap_type,6,heaps)) {
        printf("Enter heap type\n");
        scanf("%20s", heap_type);
        while (getchar() != '\n'){};
    }
    while (!compare_strings_array(struct_type,4,structs)) {
        printf("Enter search struct type type\n");
        scanf("%20s", struct_type);
        while (getchar() != '\n'){};
    }
    printf("Let's enter department start date and time\n");
    while ((str_to_int(buff,&start_year) == 1) && (!(start_year > 0) && !(start_year < 2025))){
        printf("Enter start year\n");
        scanf("%4s", buff);
        while (getchar() != '\n'){};
    }
    while ((str_to_int(buff,&end_year) == 1) && (!(end_year > 0) && !(end_year < 2025))){
        printf("Enter start year\n");
        scanf("%4s", buff);
        while (getchar() != '\n'){};
    }



}
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
     int MAX_PRIORITY;
    if (str_to_int(argv[1],&MAX_PRIORITY)){
        printf("You enter not a number or too big number");
        return 0;
    }
    else if (check_files(argc, argv)) {
        printf("Check the files names\n");
        return 0;
    }
    else if (MAX_PRIORITY < 0) {
        printf("Max priority can't be less than 0\n");
        return 0;
    }
//    while (1){
    FILE* file = fopen(argv[2], "w");
//    generate(file);
//    fclose(file);
    construct_options(file);
    fclose(file);
//    if (ask_for_generating() == 49){
//        printf("bruh\n");
//        generate(file);
//    }
//    else{
//        printf("ok\n");
//
//    }
    file1 = fopen(argv[2], "r");
    departments_option* deps_option;
    create_departments_option(&deps_option,file1);
    deps_option->max_priority = MAX_PRIORITY;
    print_dep_ops(deps_option);
    departments* dep = create_departments(deps_option);
    start_work(dep,argc,argv);
    close_department(dep);
    }
//}