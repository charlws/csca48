#include <stdio.h>

int main() {
    if (1) {
        int a = 42;
        int *(ptr) = &a;
        printf("ptr a: %p\n", ptr);
    }
    int c = 42;
    int *(ptr) = &c;
    printf("ptr c: %p\n", ptr);
    if (1) {
        int b = 42;
        int *(ptr) = &b;
        printf("ptr b: %p\n", ptr);
    }
    return 0;
}