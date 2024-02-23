#include "functions.h"
#include <string.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Invalid amount of arguments\n");
        return 0;
    }
    FILE *source;
    FILE *dest;
    if (!strcmp(argv[1], argv[2])) {
        printf("given input and output files are the same\n");
        return 0;
    }
    if ((source = fopen(argv[1], "r")) == NULL) {
        printf("Couldn't open file at %s\n", argv[1]);
        return 0;
    }
    if ((dest = fopen(argv[2], "w")) == NULL) {
        printf("Couldn't open file at %s\n", argv[2]);
        fclose(source);
        return 0;
    }
    if(read_from_file(source, dest) == memory_error)
    {
        fclose(source);
        fclose(dest);
        printf("memory error\n");
        return 0;
    }
    fclose(source);
    fclose(dest);
    printf("Program finished\n");
    return 0;
}