#include <stdio.h>
#include <math.h>

int main() {
    double pi = 3.14159265358;
    long long t = 1;
    for (int i = 1; i < 10; i++) {
        t *= 10;
        printf("%f\n", floor(pi * t) / t);
        // consider using "sprintf"
    }
    return 0;
}