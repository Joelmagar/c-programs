
// Armstrong number

#include <stdio.h>
#include <math.h>
int main(){
int num,baseNum,sum,remainder,digits;
printf("Enter your number\n");
scanf("%d",&num);

baseNum = num;

while(baseNum != 0){
    ++digits;
    baseNum /= 10;

}
baseNum = num;

while(baseNum != 0){
    
    remainder = baseNum % 10;

    sum += round(pow(remainder,digits));
baseNum /=10;
}

if(sum == num){
    printf("It is an armstrong number.");
}

else{
    printf("It is not an armstrong number.");

}

    return 0;
}
