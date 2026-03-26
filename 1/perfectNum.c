// Find a number  which  sum of divisible  number is  equal to the number // perfect number

#include <stdio.h>

int main () {
    int num,sum = 0;
    printf("Enter your number\n");
    scanf("%d",&num);
    
    for(int i =1;i<num;i++){
        
        if(num%i == 0){
          sum+=i;
        }
    }


    if(sum == num){
        printf("The number is a perfect number.\n");
        
    }else{
         
        printf("The number is not a perfect number.\n");
     }

    return 0;
}