// Swap two numbers

#include <stdio.h>

int main () {
    int a,b;
    printf("Enter your first number\n");
    scanf("%d",&a);
    printf("Enter your second number\n");
    scanf("%d",&b);

    a = a^b;
    b = a^b;
    a = a^b;
    printf("Value of a is %d and b is %d\n",a,b);
    return 0;
}