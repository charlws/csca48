#include <stdio.h>

#define GET_VARIABLE_NAME(Variable) (#Variable)

int main() {
    int x = 0;
    printf("%s = %d\n", GET_VARIABLE_NAME(x), x);
    return 0;
}