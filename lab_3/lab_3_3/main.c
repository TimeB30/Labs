#include "functions.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Invalid amount of arguments\n");
        return 0;
    }
    if (!(argv[2][0] == '-' || argv[2][0] == '/') || !(argv[2][1] == 'a' || argv[2][1] == 'd')) {
        printf("Invalid flag given\n");
        return 0;
    }

    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Couldn't open file for reading at %s", argv[1]);
        return 0;
    }

    struct Employee *employees;
    size_t size;
    int flag = read_from_file(in, &employees, &size);
    fclose(in);
    switch (flag) {
        case memory_error: {
            printf("memory error sowwy\n");
            return 0;
        }
        case invalid_file_content: {
            printf("Invalid file content\n");
            return 0;
        }
        default: {
            printf("File loaded into memory. Sorting with key '%s'", argv[2]);
        }
    }
    fflush(stdout);

    if (argv[2][1] == 'a') qsort(employees, size, sizeof(struct Employee), a_compare);
    else qsort(employees, size, sizeof(struct Employee), d_compare);
    printf("Collection sorted successfully\n");
    FILE *out = fopen(argv[3], "w");
    if (out == NULL) {
        printf("Couldn't open file for writing at %s\n", argv[3]);
        return 0;
    }
    size_t i;
    for (i = 0; i < size; i++) {
        if (write_to_file(&employees[i], out) < 0) {
            printf("Couldn't write to file, sorry :<\n");
            break;
        }
    }

    printf("Sorted collection written to file %s\n", argv[3]);
    for (i = 0; i < size; i++)
    {
        free(employees[i].first_name);
        free(employees[i].last_name);
    }
    free(employees);
    fclose(out);
    return 0;
}