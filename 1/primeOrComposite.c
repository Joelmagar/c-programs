// Check whether the number is prime or composite 

#include <stdio.h>

int main () {
 int num,count=0;

 printf("Enter your number\n");
 scanf("%d",&num);

 for (int i = 1; i < (num/2) ; i++) {
if(num%i ==0){
    ++count;
}

 }
 if(count >1){
     printf("Number is a Composite number.");
}
else{
    
    printf("Number is a prime number.");
}
 
    return 0;
}