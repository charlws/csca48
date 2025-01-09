#include <stdio.h>
#define N 100

int main() {
    for (int i = 1; i*i <= N; i++) {
        printf("%d = %d*%d\n", i * i, i, i);
    }
    return 0;
}