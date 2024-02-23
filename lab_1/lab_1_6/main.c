#include "functions.h"

int main(int argc, char** argv)
{
    int check = 0;
    double epsilon;
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    double d = 0.0;
    char* ptr = "";

    if(argc != 2)
    {
        printf("wrong amount of arguments given\n");
        return 0;
    }

    check = check_double(&argv[1]);
    switch(check)
    {
        case negative_or_zero:
        {
            printf("\nAccuracy can't be negative or zero.");
            return 0;
        }
        case not_a_number:
        {
            printf("\nInvalid accuracy given.");
            return 0;
        }
        case positive:
        {
            epsilon = strtod(argv[1], &ptr);
            a = trapezoid(task_a, 0, 1, epsilon);
            b = trapezoid(task_b, 0, 1, epsilon);
            c = trapezoid(task_c, 0, 1, epsilon);
            d = trapezoid(task_d, 0, 1, epsilon);
            double result[] = {a, b, c, d};

            for(int i = 0; i < 4; i++)
            {
                if(result[i] == INFINITY || result[i] == NAN)
                {
                    printf("couldn't calculate the Integral with given value\n");
                }
                else
                {
                    printf("%lf\n", result[i]);
                }
            }
            return 0;
        }
        default:
        {
            printf("Internal error sry\n");
            break;
        }
    }
    printf("%lf\n%lf\n%lf\n%lf\n", a, b, c, d);
    return 0;
}