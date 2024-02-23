#include "functions.h"

int main(int argc, char** argv) {
    if(argc != 3){
        printf("\nWrong amount of arguments given. Exiting.\n");
        return 0;
    }
    if(!is_number(argv[1])){
        printf("\n\"%s\" is not a valid number. Exiting.\n", argv[1]);
        return 0;
    }
    if(argv[2][2] != '\0' || argv[2][0] != '/' && argv[2][0] != '-'){
        printf("Invalid flag. Exiting.\n");
        return 0;
    }

    char flag;
    int given_number;
    int given_number_length;
    given_number_length= strlen(argv[1]);
    char given_number_string[given_number_length];

    flag = argv[2][1];
    given_number = atoi(argv[1]);
    given_number_string[given_number_length] = '\0';
    itoa(given_number, given_number_string, 10);
    if(strcmp(given_number_string, argv[1]) != 0){
        printf("given number is over the limit of int.\n");
        return 0;
    }

    int* array_of_multiples;
    int count_of_multiples;
    
    long long int** exponent_table;
    int sum_result;
    char* factorial_result;
    size_t factorial_length;


    switch(flag){
        case 'h':
        {   if(given_number == 0){
            printf("Thou Shall Not Divide by Zero!\n");
            return 0;
        }
            multiples(given_number, &array_of_multiples, &count_of_multiples);

            if(array_of_multiples){
                printf("Numbers that are multiples for %d are: ", given_number);
                for(int i = 0; i < count_of_multiples; i++){
                    printf("%d ",array_of_multiples[i]);
                }
                free(array_of_multiples);
                return 0;
            }else{
                if(count_of_multiples == -1){
                    printf("Internal Error.\n");
                    free(array_of_multiples);
                    return 1;
                }
                if(count_of_multiples == 0){
                    printf("Given number is more than 100.\n");
                    free(array_of_multiples);
                    return 0;
                }
            }
        }
        case 'p':
        {
            if(given_number == 1 || given_number == 0){
                printf("%d is not considered a prime number.\n", given_number);
                return 0;
            }
            printf("%d is a %s number.", given_number, is_prime(given_number) ? "prime" : "composite");
            return 0;
            
        }
        case 's':
        {
            printf("%d split looks like this: ", given_number);
            for(int i = 0; i < given_number_length; i++){
                printf("%c ", argv[1][i]);
            }
            return 0;
        }
        case 'e':
        {
            if(given_number < 1 || given_number > 10){
                printf("Given number is outside the limits of function calculations.\n");
                return 0;
            }
            system("chcp 65001");
            create_table_of_powers(given_number, &exponent_table);
            if(exponent_table == NULL){
                printf("Internal Error.\n");
                free(exponent_table);
                return 1;
            }
            print_table_of_powers(given_number, &exponent_table);
            for(int i = 0; i < given_number; i++){
                free(exponent_table[i]);
            }
            free(exponent_table);
            return 0;
        }
        case 'a':
        {
            if(given_number < 1){
                printf("Gievn number is less than 1.\n");
                return 0;
            }
            if(given_number > (sqrt(INT_MAX))){
                printf("Unable to calculate due to reaching the border of int type.\n");
                return 1;
            }
            sum_result = (1+given_number)*given_number/2;
            printf("Sum of all natural numbers from 1 to %d is %d", given_number, sum_result);
            return 0;
        }
        case 'f':
        {
            factorial(given_number, &factorial_result, &factorial_length);

            if(factorial_result == NULL){
                printf("Internal Error.\n");
                return 1;
            }

            for(int i = (int)factorial_length - 1; i >= 0; i--){
                printf("%c", factorial_result[i]);
            }
            free(factorial_result);
            return 0;
        }
        default:
        {
            printf("Unknown flag: %s",argv[2]);
            return 0;
        }
    }
}