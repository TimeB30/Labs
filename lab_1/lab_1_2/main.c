#include "functions.h"

int main(int argc, char** argv) {
    if(argc != 2){
        printf("Wrong amount of arguments given. Exiting\n");
        return 0;
    }
    char* end;
    double epsilon;
    epsilon = strtod(argv[1], &end);

    if(end == argv[1]){
        printf("%s is not a valid float value.\n", argv[1]);
        return 0;
    }
    if(epsilon <= 0.0){
        printf("Accuracy can't be negative or zero.\n");
        return 0;
    }
    
    double precision = 1.0/epsilon;

    double results[15];
    results[0] = lim(lim_e, epsilon);
    results[1] = lim(lim_pi, epsilon);
    results[2] = lim(lim_ln2, epsilon);
    results[3] = lim_sqrt2(epsilon);
    results[4] = lim(lim_gamma, epsilon);

    results[5] = row(row_e, epsilon);
    results[6] = row(row_pi, epsilon);
    results[7] = row(row_ln2, epsilon);
    results[8] = row_sqrt2(epsilon, ceil(1.0/epsilon));
    results[9] = row(row_gamma, epsilon);

    results[10] = eq(eq_e, epsilon);
    results[11] = eq(eq_pi, epsilon);
    results[12] = eq(eq_ln2, epsilon);
    results[13] = eq(eq_sqrt2, epsilon);
    results[14] = eq_gamma(epsilon);

    char* constants[5] = {"e", "pi", "ln2", "sqrt2", "gamma"};
    char* ways[3] = {"LIMITS", "ROWS","EQUATIONS"};
    for(int i = 0; i < 15; i++){
        if(i%5 == 0){
            printf("\n %6c%s", ' ', ways[i/5]);
        }
        printf("\nresult for %s:", constants[i%5]);
        (results[i] != INFINITY) ? printf(" %g", floor(results[i] * precision) / precision) : printf(" couldn't calculate constant with given accuracy");
    }
    return 0;
}
