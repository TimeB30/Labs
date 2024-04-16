#include"func.h"



//void print_dep(departments* dep){
//    printf("%s\n",dep->heap_type);
//    printf("%s\n",dep->data_type);
//    printf("%u\n",dep->min_processing_time);
//    printf("%u\n",dep->max_processing_time);
//    printf("%s",dep->start_date_time);
//    printf(" %s\n",dep->end_date_time);
//    printf("%f\n",dep->overload_coefficient);
//
//}


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
//    create_departmens(deps_option);




    return 0;
}