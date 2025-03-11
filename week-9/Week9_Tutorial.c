#include <stdlib.h>
#include <stdio.h>

#define SIZE 100

// don't use inline numbers for the size to prevent using unaddressed data
// this code won't crash but still has a leak! can you spot it?

int main() {
    int *array = malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        *(array + i) = i;
    }
    for (int i = 0; i < SIZE; i++) {
        printf("%d\n", *(array + i));
    }
    return 0;
}