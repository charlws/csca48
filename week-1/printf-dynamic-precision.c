#include <stdio.h>
#include <math.h>

int main() {
    double pi = 3.14159265;
    long long t = 1;
    int i = 0;
    while(floor(pi * (t/10)) / (t/10) != pi){
        printf("%.*f\n", i, floor(pi * t) / t);
        t *= 10, i++;
    }
    return 0;
}