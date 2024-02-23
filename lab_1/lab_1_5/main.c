#include "functions.h"

int main(int argc, char** argv) {
    if(argc != 3)
    {
        printf("Invalid amount of arguments.\n");
        return 0;
    }
    double x = 0;
    double epsilon = 0;
    double precision = 0;
    char* ptr = "";
    int check_epsilon = check_double(&argv[1]);
    int check_x = check_double(&argv[2]);
    double (*func[])(int n, double epsilon, double x) = {row_a, row_b, row_c, row_d};

    switch(check_epsilon)
    {
        case negative_or_zero:
        {
            printf("Accuracy can not be negative or zero.\n");
            break;
        }
        case not_a_number:
        {
            printf("Given accuracy doesn't seem to be a valid float number.\n");
            break;
        }
        case positive:
        {
            if(check_x == not_a_number)
            {
                printf("Given value for x is not a valid float value.\n");
                break;
            }
            epsilon = strtod(argv[1], &ptr);
            x = strtod(argv[2], &ptr);
            precision = 1.0/epsilon;
            for(int i = 0; i < 4; i++)
            {
                printf("Row %c: ", (i + 'a'));
                if(fabs(x) >= 1.0 && (i == 2 || i == 3))
                {
                    printf("Row diverges on given value of x\n");
                }else
                {
                    printf("%g\n", floor(row(func[i], epsilon, x) * precision) / precision);
                }
            }
            break;
        }
        default:
        {
            printf("Unexpected error :/\n");
            break;
        }
    }
    return 0;
}