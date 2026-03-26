// Factorial of given number
#include <stdio.h>


int main(){

    int num,fact=1;
    printf("Enter your number\n");
    scanf("%d",&num);
    
    for(int i =2; i<=num;i++){
        fact = fact * i;
    }
    
    printf("Factorial of your number is : %d \n",fact);


}