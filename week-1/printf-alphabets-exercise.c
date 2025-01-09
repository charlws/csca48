#include <stdio.h>

int main() {
    for (int i = 0; i < 26; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");

    for (int i = 0; i < 26; i++) {
        printf("%c - %c\n", 'A' + i, 'a' + i);
    }
    printf("\n");

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            for (int k = 0; k < 26; k++) {
                printf("%c%c%c\n", 'A' + i, 'A' + j, 'A' + k);
            }
        }
    }

    return 0;
}