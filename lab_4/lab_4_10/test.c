#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
typedef struct{
    void* func;
}command;

int sum (int a , int b){
    return a + b;
}
int main(){

    if (!strcmp("hello ","hello")){
        printf("good\n");
    }

    return 0;
}