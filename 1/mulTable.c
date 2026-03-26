// Multiplication table of a given number upto 10


#include <stdio.h>

int main () {
    int mult , num;
    printf("Enter the number:\n");
    scanf("%d",&num);
    for (int i = 1; i <= 10; i++) {
    mult = num * i;
    printf("%d x %d = %d\n",num,i,mult);
    }
    return 0;
}