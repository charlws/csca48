#include <math.h>
#include <stdio.h>
#define WIDTH 60
#define HEIGHT 40

double pi = 3.14159265358;
int plain[105][105]; // 0: empty | 1: * | 2: "|"

int main() {
    for (int i = 0; i <= HEIGHT; i++) {
        int t = sin((double)i / HEIGHT * 2 * pi) * WIDTH / 2 + WIDTH / 2;
        printf("%02d ", i);
        for (int j = 0; j < t; j++) {
            if (j == WIDTH / 2){
                plain[i][j] = 2;
                printf("|");
            }
            else
                printf(" ");
        }
        plain[i][t] = 1;
        printf("*");
        for(int j=t+1;j<=WIDTH;j++){
            if (j == WIDTH / 2){
                plain[i][j] = 2;
                printf("|");
            }
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\n");

    for(int i=0;i<=WIDTH;i++){
        for(int j=0;j<=HEIGHT;j++){
            if(plain[j][i] == 0) printf(" ");
            else if(plain[j][i] == 1) printf("*");
            else printf("-");
        }
        printf("\n");
    }

    return 0;
}