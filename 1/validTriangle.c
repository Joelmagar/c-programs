// Check if the triangle is valid by taking 3 angles
#include <stdio.h>

int main () {
 
 int sum,a;

 for(int i =0;i<3;i++){

     printf("Enter the value of angle %d\n",i+1);
     scanf("%d",&a);
     sum+=a;
    }
    if(sum ==180){

        printf("The triangle is valid\n");
    }
    else{
        printf("The triangle  has invalid angles.\n");
    }

    return 0;
}