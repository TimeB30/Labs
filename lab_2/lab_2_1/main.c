#include "functions.h"

int main(int argc, char** argv) {
    if(argc < 2)
    {
        printf("Invalid amount of arguments.\n");
        return 0;
    }
    int check = check_flag(&argv[1]);
    if(!check)
    {
        printf("Invalid flag given.\n");
        return 0;
    }
    int k = 0;
    int count = 0;
    char* str = 0;
    char* concat_string = "";
    char* cpy = "";
    int length = 0;
    int current_random = 0;
    int total_size = 0;
    int seed = 0;
    int string_count = 0;
    int flag = (unsigned char)argv[1][1];

    switch (flag)
    {
        case 'l':
        {
            if(argc < 3)
            {
                printf("Invalid amount of arguments.\n");
                break;
            }
            count = string_length(&argv[2]);
            printf("String \"%s\" is %d symbols long.\n", argv[2], count);
            break;
        }
        case 'r':
        {
            if(reverse_str(&argv[2], &str) == memory_error)
            {
                printf("Memory error:/\n");
                break;
            }
            printf("%s reversed is %s", argv[2], str);
            break;
        }
        case 'u':
        {
            if(odd_to_upper(&argv[2], &str) == memory_error)
            {
                printf("Memory error:/\n");
                break;
            }
            printf("%s reversed is %s", argv[2], str);
            break;
        }
        case 'n':
        {
            length = string_length(&argv[2]);
            str = (char*)malloc(sizeof(char)*(length+1));
            if(str == NULL)
            {
                printf("Memory error:/\n");
                break;
            }
            k = 0;
            for(int i = 0; i < length; i++)
            {
                if(isdigit(argv[2][i]))
                {
                    str[k] = argv[2][i];
                    k++;
                }
            }
            for(int i = 0; i < length; i++)
            {
                if(isalpha(argv[2][i]))
                {
                    str[k] = argv[2][i];
                    k++;
                }
            }
            for(int i = 0; i < length; i++)
            {
                if(!isalnum(argv[2][i]))
                {
                    str[k] = argv[2][i];
                    k++;
                }
            }
            str[k] = '\0';
            printf("%s\n", str);
            free(str);
            break;
        }
        case 'c':
        {//redo
         //concat(char** str1, char** str2, char** result) { *result = malloc...}
            if(argc < 4)
            {
                printf("Invalid amount of arguments.\n");
                break;
            }
            if(argc == 4)
            {
                printf("Only one string given. result is %s", argv[2]);
                break;
            }
            if(is_number(argv[3]) == not_a_number)
            {
                printf("%s isn't a correct decimal number.\n", argv[3]);
            }
            seed = atoi(argv[3]);
            srand(seed);
            argv[3] = argv[2];
            string_count = argc - 3;
            for(int i = 3; i < argc; i++)
            {
                total_size += string_length(&argv[i]);
            }
            concat_string = (char*)malloc(sizeof(char)*(total_size + 1));
            if(concat_string == NULL)
            {
                printf("Memory error :/\n");
                break;
            }
            cpy = concat_string;
            while(string_count > 0)
            {
                current_random = 3 + (rand() % string_count);
                concatenate(&argv[current_random], &concat_string);
                argv[current_random] = argv[2+string_count];
                string_count--;
            }
            *concat_string = '\0';
            printf("%s\n", cpy);
            free(cpy);
            break;
        }
        default:
        {
            printf("Invalid flag\n");
            break;
        }
    }
    return 0;
}
