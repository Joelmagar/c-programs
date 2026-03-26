//Sum and average of n numbers

#include <stdio.h>

int main () {
int n=0,sum=0,num=0;
float avg=0.0;
    printf("Enter count of total numbers\n");
    scanf("%d",&n);
    
    for (int i = 0; i < n; i++) {
        printf("Enter number %d\n",i+1);
        scanf("%d",&num);
        sum+=num;
    }
    if(n>0){
        avg =(float)sum/n; // Allows division of decimals without discarding them
    }
    printf("The sum is %d and average is %.2f",sum,avg);
    return 0;
}