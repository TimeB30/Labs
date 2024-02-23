#include "functions.h"

int main(int argc, char** argv) {
    if(argc < 3)
    {
        printf("Wrong amount of arguments.\n");
        return 0;
    }

    if(check_flag(&argv[1]) == false)
    {
        printf("wrong flag: %s", argv[1]);
        return 0;
    }
    char flag = argv[1][1];
    char* origin_1 = "";
    char* origin_2 = "";
    char* destination = "";
    FILE* input_1;
    FILE* input_2;
    FILE* output;

    switch(flag)
    {
        case 'r':
        {
            if(argc != 5)
            {
                printf("Wrong amount of arguments.\n");
                break;
            }
            origin_1 = argv[2];
            origin_2 = argv[3];
            destination = argv[4];

            input_1 = fopen(origin_1, "r");
            if(input_1 == NULL)
            {
                printf("Couldn't open file at %s\n", origin_1);
                break;
            }

            input_2 = fopen(origin_2, "r");
            if(input_2 == NULL)
            {
                printf("Couldn't open file at %s\n", origin_2);
                fclose(input_1);
                break;
            }

            output = fopen(destination, "w");
            if(output == NULL)
            {
                printf("Couldn't create a file at %s\n", destination);
                fclose(input_1);
                fclose(input_2);
                break;
            }

            if(even_odd_term_writing(&input_1, &input_2, &output) == writing_success)
            {
                printf("Writing successful.\nResult is in file %s", destination);

            }
            else
            {
                printf("Couldn't write to file: %s", destination);
            }
            fclose(input_1);
            fclose(input_2);
            fclose(output);
            break;

        }
        case 'a':
        {
            if(argc != 4)
            {
                printf("Wrong amount of arguments.\n");
                break;
            }

            origin_1 = argv[2];
            destination = argv[3];

            input_1 = fopen(origin_1, "r");
            if(input_1 == NULL)
            {
                printf("Couldn't open file at %s\n", origin_1);
                break;
            }

            output = fopen(destination, "w");
            if(output == NULL)
            {
                printf("Couldn't create a file at %s\n", destination);
                fclose(input_1);
                break;
            }
            if(letters_to_ascii(&input_1, &output) == writing_success)
            {
                printf("Writing successful.\nResult is in file %s", destination);
            }
            else
            {
                printf("Couldn't write to file: %s", destination);
            }
            fclose(input_1);
            fclose(output);
            break;
        }
        default:
        {
            printf("Wrong flag: %c", flag);
            break;
        }
    }
    printf("\nProgram finished.\n");
    return 0;
}
