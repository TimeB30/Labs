#include "functions.h"

int main() {
    char* input = "";
    char* result = "";
    int length = 0;
    int max = -1;
    int current_string_value = 0;
    int sign = 0;

    int base = 0;
    scanf("%d", &base);
    if(base <= 0)
    {
        printf("Inappropriate base given.");
        return 0;
    }
    get_string(&input, &length);
    while(strcmp(input, "Stop") != 0)
    {

        if(get_string(&input, &length) == memory_fail)
        {
            printf("Memory allocation failed ;/\n");
            return 1;
        }
        if(strcmp(input, "Stop") == 0) break;
        if((current_string_value = to_decimal(&input, length, base, &sign)) == not_a_number)
        {
            printf("%s is not a number is system with base %d\n", input, base);
            continue;
        }
        else if(abs(current_string_value) == 0)
        {
            max = 0;
            result = "0\0";
        }
        else if(max < abs(current_string_value))
        {
            max = current_string_value;
            result = input;
        }
    }

    if(max == -1)
    {
        printf("Non of the given strings appeared to be a valid number for base %d", base);
        return 0;
    }
    printf("Highest number by modulo among given strings is %s%s",(sign == -1) ? "-" : "", result);

    char* in_system;
    for(int i = 0; i < 4; i++)
    {
        if(to_system(max, &in_system, (i+1)*9) == memory_fail)
        {
            printf("memory fail");
            return 1;
        }
        printf("\n%s%s in system with base %d: %s%s", (sign == -1) ? "-" : "", result, (i + 1) * 9,(sign == -1) ? "-" : "", in_system);
    }
    free(in_system);
    return 0;
}
