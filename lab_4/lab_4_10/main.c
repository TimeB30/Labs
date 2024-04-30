#include "func.h"

void check_errors(int status){
    if (status == -1){
        printf("You enter wrong base or number\n");
        exit(EXIT_FAILURE);
    }
    else if (status == -2){
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    else if (status == -3){
        printf("You e\n");
        exit(EXIT_FAILURE);
    }
    else if (status == -4){
        printf("You enter too long input\n");
        exit(EXIT_FAILURE);
    }
    else if (status == -5){
        printf("You enter too big or negative number\n");
        exit(EXIT_FAILURE);
    }
    else if (status == -6){
        printf("You enter not a number\n");
        exit(EXIT_FAILURE);
    }
}
void output(unsigned int num,unsigned int base){
    if ((base < 2) || (base > 36)){
        return;
    }
    unsigned int mods[33];
    int i = 0;
    while(num > 0){
        mods[i] = num % base;
        num /= base;
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
int main(int argc, char** argv){
    int status = 0;
    if (argc > 6)
    {
        printf("You enter too much arguments\n");
        return 1;
    }
    else if (argc == 0){
        printf("Enter file\n");
        return 1;
    }
    FILE* file = fopen(argv[4],"r");
    if (file == NULL){
        printf("Check file name\n");
        return 0;
    }
    unsigned int base_assign = strtouint(argv[1],10,&status);
    check_errors(status);
    unsigned int base_input = strtouint(argv[2],10,&status);
    check_errors(status);
    unsigned int base_output = strtouint(argv[3],10,&status);
    check_errors(status);
    trie* tr = create_trie();
    string* str = create_string(&status);
    add_to_string(str,'d');
    add_value_to_trie(str,249,tr,&status);
//    unsigned int num = input(base_input,&status); // works good
//    printf("%u\n",num);
    output(13,2); // works great

    return 0;
}
