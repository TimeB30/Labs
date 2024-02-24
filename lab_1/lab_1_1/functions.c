#include "functions.h"

int is_number(const char* string){
    size_t string_length = strlen(string);
    for(int i = 0; i < string_length; i++){
        if(!isdigit(string[i])) return 0;
    }
    return 1;
}

int is_prime(int number){
    if(number == 1){
        return 0;
    }
    int root = (int)ceil(sqrt(number));
    if(number%2){
        for( int i = 3; i <= root; i += 2 ){
            if(number%i == 0) return 0;
        }
    }else{
        for( int i = 2; i <= root; i++ ){
            if(number%i == 0) return 0;
        }
    }
    return 1;
}

void multiples(int number, int** array, int* amount){
    *amount = 0;
    if (number > 100){
        *array = (int*)NULL;
        return;
    }

    int x;
    x = number;
    *array = (int*)malloc(sizeof(int)*(100/number) + 1);
    if(*array == NULL){
        *amount = -1;
        return;
    }

    while(x <= 100){
        (*array)[*amount] = x;
        (*amount)++;
        x += number;
    }
}

void create_table_of_powers(int exponent, long long int*** table) {
    (*table) = (long long int **) malloc(sizeof(long long int *) * 10);
    if (*table == NULL) return;

    for (int i = 0; i < 10; i++) {
        (*table)[i] = (long long int *) malloc(sizeof(long long int) * exponent);
        if ((*table)[i] == NULL) {
            for(int j = 0; j < 10; j++){
                free((*table)[j]);
            }
            *table = NULL;
            return;
        }
    }

    for(int i = 0; i < 10; i++){
        (*table)[i][0] = i + 1;
        for(int j = 1; j < exponent; j++){
            (*table)[i][j] = (*table)[i][j-1] * (i+1);
        }
    }
}

void print_table_of_powers(int exponent, long long int*** table){
    printf("┌──────────┬");
    for(int i = 1; i < 1 + exponent; i++){
        printf("─────────────┬");
    }
    printf("\n│\\exponent │");
    for(int i = 1; i < 1 + exponent; i++) {
        printf("             │");
    }
    printf("\n│ ───────  │");
    for(int i = 1; i < 1 + exponent; i++) {
        printf("%7d      │", i);
    }
    printf("\n│___base__\\│");
    for(int i = 1; i < 1 + exponent; i++){
        printf("_____________│");
    }
    for(int i = 0; i < 10; i++) {
        printf("\n│%5d     │", i+1);
        for(int j = 0; j < exponent; j++){
            printf(" %-11lld │", (*table)[i][j]);
        }
        printf("\n│──────────│");
        for(int j = 0; j < exponent; j++){
            printf("-------------│");
        }
    }
}

size_t stirling_formula(int n){
    const double
            pi = 3.14159265358979323846,
            e = 2.7182818284590452354;
    if (n==1) return 1;

    return ceil(log10(2 * pi * n) / 2 + n * (log10(n / e)));
}

void long_arithmetics_multiplication(int x, char** result, size_t* length){
    int carry = 0;
    for(int i = 0; i < *length; i++){

        int product = ((*result)[i] - '0') * x + carry;

        carry = product / 10;
        int c = product % 10;
        (*result)[i] = c + '0';
    }
    while(carry){
        (*result)[*length] = carry%10 + '0';
        carry /= 10;
        (*length)++;
    }
}

void factorial(int given_number, char** result, size_t* result_size){
    *result_size = 1;
    char *for_realloc;
    *result = (char*)malloc(1*sizeof(char*));
    if(*result == NULL) return;

    (*result)[0] = 1 + '0';
    for(int i = 2; i <= given_number; i++){
        size_t old_size = *result_size;
        *result_size = stirling_formula(i);
        for_realloc = realloc(*result, *result_size);
        if(for_realloc == NULL)
        {
            free(*result);
            return;
        }
        *result = for_realloc;

        for(int j = (int)old_size; j < (int)*result_size; j++){
            (*result)[j]='0';
        }
        long_arithmetics_multiplication(i, &(*result), &(*result_size));
    }
}