#include "functions.h"

int main(int argc, char** argv) {
    if(argc < 2 || argc > 3)
    {
        printf("wrong amount of arguments given.\n");
        return 0;
    }
    dialogue(argv[1], argc, argv);
    return 0;
}
