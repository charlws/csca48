#include <stdio.h>

int a[100];

int main() {
    a[-10] = 1;
    printf("%d", a[-10]);
    return 0;
}