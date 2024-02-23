#include "functions.h"

int main() {
    char* result = "";
    if(add_up_strings(&result, 36, 2, "ZZZZ", "ZZZ") == wrong_system) result = "wrong_system";
    printf("%s\n", result);
    return 0;
}
