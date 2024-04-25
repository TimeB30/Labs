#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    time_t timestamp = 1711918800+86400;
    struct tm *timeinfo = localtime(&timestamp);
    printf("Дата и время: %s", asctime(timeinfo));
    return 0;

}