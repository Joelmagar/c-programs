// Display fibonacci sequence upto nth term 
#include <stdio.h>

int main () {

    int n, num =0,num2=1,sum;
    printf("Enter nth term:\n");
    scanf("%d",&n);
    
    // printf("%d\t",);
    for(int i =0;i<n;i++){

        if(i==1){
            sum= 1;
        }
        else {
            /* code here */ 
            sum = num + num2;
            num = num2;
            num2=sum;
        }
        printf("%d\t",sum);

        
    }



}