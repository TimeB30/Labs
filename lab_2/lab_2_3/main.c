#include "functions.h"


int main() {
    strct** results;
    naive_search(&results, "dd", 2, "C:\\Users\\cucurbita\\Desktop\\asd\\1.txt", "C:\\Users\\cucurbita\\Desktop\\asd\\2.txt");

    for(int i = 0; i < 2; i++)
    {
        printf("\nfile %d: [line, position]\n", i+1);
        int j = 0;
        while(results[i][j].line != 0)
        {
            printf("[%d, %d] ",results[i][j].line, results[i][j].pos);
            j++;
        }
    }
    return 0;
}
