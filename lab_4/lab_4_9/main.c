#include"func.h"
int ask_for_generating(){
    char answer;
    char* end;
    int des = 0;
    while ((des != 1) && (des != 2)) {
        printf("Do you want to add parameters?\n1) Yes\n2) No\n");
        getchar()
        des = strtol(&answer,&end,10);

    }
    return des;
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
    if (ask_for_generating()){
        printf("bruh\n");
    }
    else{
        printf("bruh\n");
    }
    file1 = fopen(argv[2], "r");
    departments_option* deps_option;
    create_departments_option(&deps_option,file1);
    deps_option->max_priority = MAX_PRIORITY;
    print_dep_ops(deps_option);
    departments* dep = create_departments(deps_option);
    start_work(dep,argc,argv);
    close_department(dep);
}