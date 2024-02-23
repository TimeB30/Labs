#include "functions.h"
#define CONSTANT 250

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        printf("Wrong amount of arguments given\n");
        return 0;
    }
    if(!is_number(argv[1]) || !is_number(argv[2]))
    {
        printf("wrong array value borders given\n");
        return 0;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    int array[CONSTANT];
    int max = -INT_MAX;
    int min = INT_MAX;
    int max_pos = 0;
    int min_pos = 0;
    srand(time(NULL));
    for (int i = 0; i < CONSTANT; i++)
    {
        array[i] = a + rand() % (b - a + 1);
        if(array[i] > max)
        {
            max = array[i]; max_pos = i;
        }
        if(array[i] < min)
        {
            min = array[i]; min_pos = i;
        }
    }
    printf("Array generated.\nMax element: [%d] = %d\nMin element: [%d] = %d\n",max_pos, array[max_pos], min_pos, array[min_pos]);
    swap(&array[min_pos], &array[max_pos]);
    printf("Max element: [%d] = %d \nMin element: [%d] = %d\n", max_pos, array[max_pos], min_pos, array[min_pos]);
    for(int i = 0; i < CONSTANT; i++)
    {
        printf("%d ", array[i]);
    }
    return 0;
}