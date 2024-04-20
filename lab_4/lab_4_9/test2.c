#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE* file = fopen("test.txt","r");
    char* w = (char*)malloc(sizeof(char)*10);
    fscanf(file,"%s",w);
    fgetc(file);
    fgetc(file);
    fscanf(file,"%s",w);
    printf("%s\n",w);
//    char letter;
//    letter = fgetc(file);
//    if (letter == EOF){
//        printf("shiit\n");
//    }
}