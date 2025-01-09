#include <stdbool.h>
#include <stdio.h>
#define N 1000

bool prime[N + 5];

int main() {
    for (int i = 0; i <= N; i++) {
        prime[i] = true;
    }
    prime[0] = prime[1] = false;

    for (int i = 2; i <= N; i++) {
        if (prime[i]) {
            for (int j = i * i; j <= N; j += i) {
                // i*i is sufficient
                // i*2~i*(i-1) are checked by previous iterations from 2 to i-1
                prime[j] = false;
            }
        }
    }

    for (int i = 2; i <= N; i++) {
        if (prime[i]) {
            printf("%d\n", i);
        }
    }
    return 0;
}