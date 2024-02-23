#include "functions.h"

double root_of_power(double x, int exponent, double eps){
    if(exponent > INT_MAX / 2 ){
        return INFINITY;
    }
    double value_current = 1;
    double value_next = (1.0/exponent)*((exponent - 1) * value_current + x/ binary_power(value_current, exponent-1));
    while(fabs(value_current - value_next) > eps){
        value_current = value_next;
        value_next = (1.0/exponent)*((exponent - 1) * value_current + x/ binary_power(value_current, exponent-1));
    }
    return value_next;
}

double binary_power(double base, unsigned long long exponent){
    double v = 1.0;
    while(exponent){
        if(exponent & 1){
            v *= base;
        }
        base *= base;
        exponent >>= 1;
    }
    return v;
}

int check_flag(char** word){
    if(((*word)[0] != '-' && (*word)[0] != '/') || strlen(*word) != 2) return 0;
    return 1;
}

int is_number(const char* string){
    size_t string_length = strlen(string);
    int i = 0;
    if((string)[0] == '-'){
        i = 1;
    }
    for( ; i < string_length; i++){
        if(!isdigit(string[i])) return 0;
    }
    return 1;
}

int check_double(char** word){
    double value;
    char* end;
    value = strtod(*word, &end);

    if(*end != 0){
        return 0;
    }
    if(value <= 0.0){
        return -1;
    }
    return 1;
}

void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

int partition(double** array, int low, int high, double epsilon) {

    double pivot = (*array)[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if(fabs((*array)[j] - pivot) < epsilon) continue;
        if ((*array)[j] < pivot) {
            i++;
            swap(&(*array)[i], &(*array)[j]);
        }
    }

    swap(&(*array)[i + 1], &(*array)[high]);
    return (i + 1);
}

void quicksort(double** array, int low, int high, double epsilon) {
    if (low < high) {
        int pivot = partition(array, low, high, epsilon);

        quicksort(array, low, pivot - 1, epsilon);
        quicksort(array, pivot + 1, high, epsilon);
    }
}

int generate_permutation(double** array, int array_length, double epsilon){
    int j = array_length - 2;
    while (j != -1 && ((*array)[j] > (*array)[j+1]) || fabs((*array)[j] - (*array)[j+1]) < epsilon) {
        j--;
    }
    if (j == -1){
        return 0;
    }

    int k = array_length - 1;
    while ((*array)[j] >= (*array)[k]) k--;
    swap(&(*array)[j], &(*array)[k]);

    int left = j + 1;
    int right = array_length - 1;
    while (left < right){
        left += 1;
        right -= 1;
        swap(&(*array)[left], &(*array)[right]);
    }
    return 1;
}

int solve_equation(double** permutation, double** solutions, int amount_of_solutions, double epsilon){
    double discriminant;
    double a = (*permutation)[0];
    double b = (*permutation)[1];
    double c = (*permutation)[2];

    double solution_1;
    double solution_2;

    if(a < epsilon){
        solution_1 = -c/b;
        solution_2 = solution_1;
    }else{
        discriminant = binary_power(b, 2) - 4 * a * c;
        if(discriminant < 0){
            return 0;
        }
        solution_1 = (-b + root_of_power(discriminant, 2, epsilon)) / (2*a);
        solution_2 = (-b - root_of_power(discriminant, 2, epsilon)) / (2*a);
    }
    (*solutions)[0] = solution_1;
    (*solutions)[1] = solution_2;
    return 1;
}