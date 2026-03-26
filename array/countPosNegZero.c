// Count of positive , negative and zero elements in an input array

#include <stdio.h>

int main () {
    int n,countP=0,countN=0,countZ=0;
    printf("Enter the count of array elements\n");
    scanf("%d",&n);
    int arr[n];
    for (int i = 0; i < n ; i++) {
        printf("Enter element %d\t:",i+1);
        scanf("%d",&arr[i]);
   if(arr[i] > 0){
    ++countP;
   }
   else if(arr[i]<0){
    ++countN;
   }
   else{
    ++countZ;
   }
}
printf("Count of postive number is %d , negative number is %d and zero is %d",countP,countN,countZ);
  
    return 0;
}