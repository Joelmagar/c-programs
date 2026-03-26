// Count of odd or even elements in an input array

#include <stdio.h>

int main () {
    int n,countE=0,countO=0;
    printf("Enter the count of array elements\n");
    scanf("%d",&n);
    int arr[n];
    for (int i = 0; i < n ; i++) {
        printf("Enter element %d\t:",i+1);
        scanf("%d",&arr[i]);
   if(arr[i]%2==0){
    ++countE;
   }
   else{
    ++countO;
   }
}
printf("Count of odd number is %d and even number is %d",countO,countE);
  
    return 0;
}