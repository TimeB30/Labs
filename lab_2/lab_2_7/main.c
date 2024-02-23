#include "functions.h"

#define EPSILON 1e-10
#define A_BORDER 0
#define B_BORDER 1

int main() {

    printf("%lf", equation(A_BORDER, B_BORDER, EPSILON, eq_));
    return 0;
}
