// Sum of square of first n natural numbers
#include <stdio.h>

int main () {
    int n,sum=0;
    printf("Enter the number\n");
    scanf("%d",&n);
    for(int i =1;i<=n;i++){
        sum+= i*i;
    }
    
    printf("Sum of square of %d first natural is %d\n",n,sum);
    
    return 0;
}