#include "functions.h"

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        printf("Wrong amount of arguments\n");
        return 0;
    }
    if(check_flag(&argv[1]) == 0)
    {
        printf("Invalid flag: %s", argv[1]);
        return 0;
    }

    char flag = 0;
    char* origin = "";
    char* destination = "";
    int dash_position = 0;
    char* original_file_itself = "";

    origin = argv[2];

    if(argv[1][1] == 'n')
    {
        if(argc != 4)
        {
            printf("Invalid amount of arguments given\n");
            return 0;
        }
        flag = argv[1][2];
        destination = argv[3];
    }
    else
    {
        flag = argv[1][1];
        if(argc != 3)
        {
            printf("Invalid amount of arguments given\n");
            return 0;
        }
        size_t length = strlen(argv[2]);
        dash_position = find_dash(&argv[2], length);
        original_file_itself = &argv[2][dash_position+1];
        destination = (char*)malloc(sizeof(char)*(length+2));
        if(destination == NULL)
        {
            printf("Internal error.\n");
            free(destination);
            return 0;
        }

        snprintf(destination, dash_position+2, "%s", origin);
        snprintf(destination, length+5,"%sout_%s", destination, original_file_itself);
    }

    FILE* or = fopen(origin, "r");
    if(or == NULL)
    {
        printf("Unable to read file at \"%s\"\n", origin);
        return 0;
    }

    FILE* dest = fopen(destination, "w");
    if(dest == NULL)
    {
        printf("Unable to create file at \"%s\"\n", destination);
        fclose(or);
        free(or);
        return 0;
    }

    switch(flag)
    {
        case 'd':
        {
            if(exclude_arabic_digits(&or, &dest) == writing_fail)
            {
                printf("Error writing to file: %s\n", destination);
                fclose(or);
                fclose(dest);
                free(destination);
                break;
            }
            fclose(or);
            fclose(dest);
            printf("Excluded arabic digits from file: %s\nResult is in file %s\n", origin, destination);
            free(destination);
            break;
        }
        case 'i':
        {
            if(count_latin_letters(&or, &dest) == writing_fail)
            {
                printf("Error writing to file: %s\n", destination);
                fclose(or);
                fclose(dest);
                free(destination);
                break;
            }
            fclose(or);
            fclose(dest);
            printf("Counted latin letters in file: %s\nResult is in file %s\n", origin, destination);
            free(destination);
            break;

        }
        case 's':
        {
            if(count_non_latin_arabic(&or, &dest) == writing_fail)
            {
                printf("Error writing to file: %s\n", destination);
                fclose(or);
                fclose(dest);
                free(destination);
                break;
            }
            fclose(or);
            fclose(dest);
            printf("Counted symbols that are not latin letters, arabic digits or spaces in file: %s\nResult is in file %s\n", origin, destination);
            free(destination);
            break;
        }
        case 'a':
        {
            if(swap_with_ascii16(&or, &dest) == writing_fail)
            {
                printf("Error writing to file: %s\n", destination);
                fclose(or);
                fclose(dest);
                free(destination);
                break;
            }
            fclose(or);
            fclose(dest);
            printf("non-numbers are rewritten with 16-bit ASCII code in file: %s\nResult is in file %s\n", origin, destination);
            free(destination);
            break;
        }
        default:
        {
            printf("Invalid flag given: %s", argv[1]);
            fclose(or);
            fclose(dest);
            free(destination);
            break;
        }
    }
    return 0;
}
