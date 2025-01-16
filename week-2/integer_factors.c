#include <stdio.h>

int factor(int x, int y) {
    for (int i = 0; y * i <= x; i++) {
        if (y * i == x) return 1;
    }
    return 0;
}

int main() {
    for (int x = 1; x <= 13; x++) {
        for (int y = 1; y <= x; y++) {
            if (factor(x, y)) {
                printf("y=%d is a factor of x=%d\n", y, x);
            }
        }
    }
    return 0;
}