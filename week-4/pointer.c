#include <stdio.h>

void foo(int* p) {
    *(p) = 10;
}

int main() {
    int x = 5;
    int* p = &x;  // we can use void* pointer to point to anything
    char y = 'c';
    int** p2 = &p;
    printf("%p\n", p2);

    foo(&x);
    printf("%d\n", x);

    int* p3 = NULL;
    printf("%d\n", *p3);
    return 0;
}