#include <stdio.h>
#include <string.h>

int main(){
    char a[4];
    const char b[10] = "abcdefgh";
    char c[10];
    strcpy(a, "123"); // can't do 1234 because there's a \0
    strcpy(c, "5678");
    strcat(a, c);
    c[4] = '0'; // what if we remove the \0?
    printf("%s\n", a);
    printf("%s\n", b); // const can be modified with pointer/overflow!
    printf("%s\n", c);
    return 0;
}