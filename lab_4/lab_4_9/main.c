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
void get_date_time_from_user(long* date_time){
    char buff[21];
    buff[0] = 't';
    while ((str_to_int(buff, &date_time[0]) == 1) || ((date_time[0] < 1900) || (date_time[0] > 2024))) {
        printf("Enter year\n");
        scanf("%20s", buff);
        while (getchar() != '\n') {};
    }
    buff[0] = 't';
    while ((str_to_int(buff, &date_time[1]) == 1) || ((date_time[1] == 0) || (date_time[1] > 12))) {
        printf("Enter month\n");
        scanf("%20s", buff);
        while (getchar() != '\n') {};
    }
    buff[0] = 't';
    while (1) {
        if ((str_to_int(buff, &date_time[2]) == 0) && (date_time[2] < 32) && (date_time[2] != 0)){
            if (date_time[1] == 2){
                if (date_time[2] <= 28){
                    break;
                }
                printf("In this month are 28 days\n");
            }
            else if ((date_time[1] == 4) || (date_time[1] == 6) || (date_time[1] == 9) || (date_time[1] == 11)){
                if (date_time[2] <= 30){
                    break;
                }
                printf("In this month are 30 days\n");
            }
            else{
                break;
            }
        }
        printf("Enter day\n");
        scanf("%20s", buff);
        while (getchar() != '\n') {};
    }
    buff[0] = 't';
    while ((str_to_int(buff, &date_time[3]) == 1) || ((date_time[3] < 0) || (date_time[3] > 23))) {
        printf("Enter hour\n");
        scanf("%20s", buff);
        while (getchar() != '\n') {};
    }
    buff[0] = 't';
    while ((str_to_int(buff, &date_time[4]) == 1) || ((date_time[4] < 0) || (date_time[4] >= 60))) {
        printf("Enter minute\n");
        scanf("%20s", buff);
        while (getchar() != '\n') {};
    }
    buff[0] = 't';
    while ((str_to_int(buff, &date_time[5]) == 1) || ((date_time[5] < 0) || (date_time[5] >= 60))) {
        printf("Enter second\n");
        scanf("%20s", buff);
        while (getchar() != '\n') {};
    }
}
void construct_options(FILE* file) {
    struct tm date_time_tm;
    char heap_type[14];
    char struct_type[17];
    char heaps[6][18] = {"BinaryHeap", "BinomialHeap", "FibonacciHeap", "SkewHeap", "LeftistHeap", "Treap"};
    char structs[4][18] = {"HashSet", "DynamicArray", "BinarySearchTree", "Trie"};
    char buff[21] = "t";
    long  start_date_time[6];
    long  end_date_time[6];
    long min_process_time;
    long max_process_time;
    long department_quantity;
    long* operators_quantity;
    double overload_coefficient;
    while (!compare_strings_array(heap_type, 6, heaps)) {
        printf("Enter heap type\n");
        scanf("%13s", heap_type);
        while (getchar() != '\n') {};
    }
    while (!compare_strings_array(struct_type, 4, structs)) {
        printf("Enter search struct type type\n");
        scanf("%16s", struct_type);
        while (getchar() != '\n') {};
    }
    buff[0] = 't';
    printf("Let's enter department start date and time\n");
    get_date_time_from_user(start_date_time);
    printf("Now enter department end date and time\n");
    do {
        printf("Remember end date later than start date\n");
        get_date_time_from_user(end_date_time);
    }
    while(compare_dates(start_date_time,end_date_time));

    while((str_to_int(buff,&min_process_time) == 1) || (min_process_time < 1)){
        printf("Enter min process time (minutes)\n");
        scanf("%20s", buff);
        while (getchar() != '\n') {};
    }
    buff[0] = 't';
    while((str_to_int(buff,&max_process_time) == 1) || (min_process_time < 1) || (max_process_time < min_process_time)){
        printf("Enter max process time (minutes)\n");
        scanf("%20s", buff);
        while (getchar() != '\n') {};
    }
    buff[0] = 't';
    while((str_to_int(buff,&department_quantity) == 1) || (department_quantity < 1) || (department_quantity > 100)){
        printf("Enter department quantity\n");
        scanf("%20s", buff);
        while (getchar() != '\n') {};
    }
    operators_quantity = (long*)malloc(sizeof(long)*department_quantity);
    if (operators_quantity == NULL){
        memory_error();
    }
    double eps_num = eps();
    for (int i = 0; i < department_quantity; i++){
        buff[0] = 't';
        while ((str_to_int(buff,&operators_quantity[i]) == 1) || (operators_quantity[i] < 10) || (operators_quantity[i] > 50)){
            printf("Enter department № %d operator quantity\n",i+1);
            scanf("%20s",buff);
            while (getchar() != '\n') {};
        }
    }
    buff[0] = 't';
    while ((str_to_double(buff,&overload_coefficient) == 1) || ((overload_coefficient - 1.0) < eps_num)){
        printf("Enter overload coefficient\n");
        scanf("%20s",buff);
    }
    fprintf(file,"%s\n",heap_type);
    fprintf(file,"%s\n",struct_type);
    fprintf(file,"%04ld-%02ld-%02ld %02ld:%02ld:%02ld\n",start_date_time[0],start_date_time[1],start_date_time[2],start_date_time[3],start_date_time[4],start_date_time[5]);
    fprintf(file,"%04ld-%02ld-%02ld %02ld:%02ld:%02ld\n",end_date_time[0],end_date_time[1],end_date_time[2],end_date_time[3],end_date_time[4],end_date_time[5]);
    fprintf(file,"%ld\n",min_process_time);
    fprintf(file,"%ld\n",max_process_time);
    fprintf(file,"%ld\n",department_quantity);
    for (int i = 0; i < department_quantity; i++){
        fprintf(file,"%ld ",operators_quantity[i]);
    }
    fprintf(file,"\n");
    fprintf(file,"%lf",overload_coefficient);
    free(operators_quantity);
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
    FILE *file1;
    if (argc < 2) {
        printf("Enter files\n");
        return 0;
    }
    long MAX_PRIORITY;
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
    struct timespec current_time;
    clock_gettime(CLOCK_REALTIME, &current_time);
    unsigned int seed = (unsigned int)(current_time.tv_sec * 1000 + current_time.tv_nsec / 1000000);
    srand(seed);
    create_applications(argc, argv);
    FILE* file = fopen(argv[2], "w");
    if (ask_for_generating() == 50){
        printf("bruh\n");
        generate(file);
    }
    else{
        construct_options(file);
        printf("ok\n");
    }
    fclose(file);
    file1 = fopen(argv[2], "r");
    departments_option *deps_option;
    create_departments_option(&deps_option, file1);
    deps_option->max_priority = MAX_PRIORITY;
    print_dep_ops(deps_option);
    departments *dep = create_departments(deps_option);
    start_work(dep, argc, argv);
    close_department(dep);
    }
