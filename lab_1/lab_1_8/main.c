#include "functions.h"

int main(int argc, char** argv) {

    if(argc != 3)
    {
        printf("Invalid amount of arguments.\n");
        return 0;
    }

    FILE* input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Couldn't open file at %s", argv[1]);
        return 0;

    }

    FILE* out = fopen(argv[2], "w");
    if(out == NULL)
    {
        printf("Couldn't create file at %s", argv[1]);
        fclose(input);
        return 0;
    }

    int c = '0';
    int base;
    int num;
    char* string;
    int length;
    int sign = 1;
    
    while(c != EOF)
    {
        if(get_string(&string, &c, &length, input) == memory_fail)
        {
            printf("Memory fail, my bad :/\n");
            break;
        }
        base = notation(&string, length);
        num = to_decimal(&string, length, base, &sign);
        if(num == not_a_number || base == 0)
        {
            if(fprintf(out, "2 0 ") == EOF) {
                printf("Couldn't write to file, sorry????\n");
                break;
            }
        }else
        {
            if(fprintf(out, "%d %d ", base, num * sign) == EOF)
            {
                printf("Couldn't write to file, sorry????\n");
                break;
            }
        }
        skip_splits(&input, &c);
    }

    fclose(input);
    fclose(out);
    return 0;
}
