

#ifndef LAB_3_1_FUNCTIONS_H
#define LAB_3_1_FUNCTIONS_H

enum exit_codes
{
    memory_error,
    success,
};

int to_system(char** result, unsigned int n, int exponent);
void remove_trailing_zeroes(char** string);

#endif //LAB_3_1_FUNCTIONS_H
