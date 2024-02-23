#include <stdio.h>
#include "functions.h"

int main(int argc, char** argv) {
    if(argc < 2){
        printf("\nNo flags were given");
        return 0;
    }
    if(check_flag(&argv[1]) == 0){
        printf("\nInvalid flag: %s", argv[1]);
        return 0;
    }
    char flag = argv[1][1];
    double* permutation = NULL;
    double* roots = NULL;

    char* ptr = "";
    double epsilon = 0;
    int check = 0;
    int number_1 = 0;
    int number_2 = 0;

    double max = 0;
    double sum = 0;
    double side = 0;

    switch (flag){
        case 'q':
        {
            if(argc != 6){
                printf("\nInvalid amount of arguments after flag.\nExpected: 4\nPut:%d", argc-2);
                return 0;
            }

            check = check_double(&argv[2]);
            switch(check) {
                case -1: {
                    printf("\nAccuracy can't be negative or zero.");
                    return 0;
                }
                case 0: {
                    printf("\nInvalid accuracy given.");
                    return 0;
                }
                case 1:
                {
                    ptr = argv[2];
                    epsilon = strtod(argv[2], &ptr);
                    if(!(is_number(argv[3]) && is_number(argv[4]) && is_number(argv[5]))){
                        printf("\nWrong coefficients given");
                        return 0;
                    }
                    permutation = (double*)malloc(sizeof(double)*EQUATION_COEFFICIENTS);
                    if(permutation == NULL){
                        printf("\nInternal error lol.");
                        free(permutation);
                        return 1;
                    }

                    for(int i = 0; i < EQUATION_COEFFICIENTS; i++){
                        if(!check_double(&argv[3 + i])){
                            printf("%s is not a valid float value ;(\n", argv[3+i]);
                            free(permutation);
                            return 0;
                        }
                        permutation[i] = strtod(argv[3 + i], &ptr);
                    }
                    roots = (double*)malloc(sizeof(double)*ROOTS);
                    if(roots == NULL){
                        printf("Internal Error sorry T_T\n");
                        free(permutation);
                        free(roots);
                        return 1;
                    }
                    quicksort(&permutation, 0, EQUATION_COEFFICIENTS - 1, epsilon);

                    printf("solutions:\n(%g) * x^2 + (%g) * x + (%g) = 0:\n", permutation[0], permutation[1], permutation[2]);
                    if(!solve_equation(&permutation, &roots, 2, epsilon)){
                        printf("both roots are within the field C of complex numbers\n");
                    }else{
                        printf("x_1 = %g\nx_2 = %g\n", roots[0], roots[1]);
                    }

                    while(generate_permutation(&permutation, EQUATION_COEFFICIENTS, epsilon)){
                        printf("\n(%g) * x^2 + (%g) * x + (%g) = 0:\n", permutation[0], permutation[1], permutation[2]);

                        if(!solve_equation(&permutation, &roots, 2, epsilon)){
                            printf("both roots are within the field C of complex numbers\n");
                        }else{
                            printf("x_1 = %g\nx_2 = %g\n", roots[0], roots[1]);
                        }
                    }
                    free(roots);
                    free(permutation);
                    return 0;
                }
                default:
                {
                    printf("\nUnexpected error.");
                    return 1;
                }
            }
        }
        case 'm':
        {
            if(argc != 4){
                printf("\nInvalid amount of arguments after flag.\nExpected: 2\nPut:%d", argc-2);
                return 0;
            }
            if(!(is_number(argv[2]) && is_number(argv[3]))){
                printf("\nInvalid numbers given.");
                return 0;
            }
            number_1 = atoi(argv[2]);
            number_2 = atoi(argv[3]);
            printf("\n%d is%s a multiple for %d", number_1, (number_1 % number_2 == 0) ? "" : " not", number_2);
            return 0;

        }
        case 't':
        {
            if(argc != 6){
                printf("\nInvalid amount of arguments after flag.\nExpected: 4\nPut:%d", argc-2);
                return 0;
            }
            check = check_double(&argv[2]);
            switch(check) {
                case -1: {
                    printf("\nAccuracy can't be negative or zero.");
                    return 0;
                }
                case 0: {
                    printf("\nInvalid accuracy given.");
                    return 0;
                }
                case 1: {
                    ptr = argv[2];
                    epsilon = strtod(argv[2], &ptr);
                    max = 0.0;
                    sum = 0.0;
                    for (int i = 3; i <= 5; i++) {
                        check = check_double(&argv[i]);
                        switch (check) {
                            case -1: {
                                printf("\nSize of triangle side can't be negative or zero.");
                                return 0;
                            }
                            case 0: {
                                printf("\n%s is not a side size", argv[i]);
                            }
                            case 1: {
                                ptr = argv[2];
                                side = strtod(argv[i], &ptr);
                                max = (max - side > epsilon) ? max : side;
                                sum += side;
                                break;
                            }
                            default: {
                                printf("\nUnexpected error.");
                                return 1;
                            }
                        }
                    }
                    printf("\nIt is %s for a triangle with given sides to exist.", sum - max > max ? "possible" : "impossible");
                    return 0;
                    default: {
                        printf("\nUnexpected error.");
                        return 1;
                    }
                }
            }
        }
        default:{
            printf("\nInvalid flag: %s", argv[1]);
            return 0;
        }
    }
}
