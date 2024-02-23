#include "functions.h"
#define EPSILON 1e-5
#define SYSTEM 2

int main() {
    char** results;

    is_final(EPSILON, SYSTEM, &results, 4, 0.60004883632064, 0.020408093929291, 0.6711110475328233506580634, 0.357);
    for(int i = 0; i < 4; i++)
    {
        printf("%s\n", results[i]);
    }
    return 0;
}
