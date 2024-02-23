#include "functions.h"

int main() {
    srand(time(NULL));
    size_t a_length = 10 + rand() % (10000 - 10 + 1);
    int* A;
    A = (int*)malloc(a_length * sizeof(int));
    if(A == NULL){
        printf("Internal error\n");
        return 1;
    }
    for(int i = 0; i < a_length; i++){
        A[i] = -1000 + rand() % (1000 - -1000 + 1);
    }

    size_t b_length = 10 + rand() % (10000 - 10 + 1);
    int* B;
    B = (int*)malloc(b_length * sizeof(int));
    if(B == NULL){
        printf("Internal error\n");
        return 1;
    }
    for(int i = 0; i < b_length; i++){
        B[i] = -1000 + rand() % (1000 - -1000 + 1);
    }
    qsort(B, b_length, sizeof(int), (int (*)(const void *, const void *)) compare);

    int C[a_length];
    for(int i = 0; i < a_length; i++){
        int to_add = find_nearest(&B, b_length, A[i]);
        C[i] = A[i] + to_add;
        printf("%d %d %d\n", A[i], to_add, C[i]);
    }
    printf("size %d smallest %d biggest %d\n", b_length, B[0], B[b_length-1]);
    for(int i = 0; i < b_length; i++){
        printf("%d ", B[i]);
    }
    return 0;
}