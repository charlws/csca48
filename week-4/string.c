#include <stdio.h>
#include <string.h>

int main(){
    char str[20] = "0000000?????";
    strcpy(str, "Toronto"); // adds '\0' automatically
    printf("%s\n", (str + 8)); // doesn't overwrite stuff after the copied string
    strcat(str, ", Canada"); // adds '\0' automatically
    printf("%s\n%d\n", str, (int)strlen(str));
    return 0;
}