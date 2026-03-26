// Sum and average of element of input array 


#include <stdio.h>

int main () {
    int n,sum=0;
    float average;
    printf("Enter the count of array elements\n");
    scanf("%d",&n);
    int arr[n];
    for (int i = 0; i < n ; i++) {
    printf("Enter element %d\t:",i+1);
    scanf("%d",&arr[i]);
    sum+=arr[i];
    }
    average = (float)sum/n;
    printf("Sum of array is %d and Average is %.2f\n",sum,average);
  

    return 0;
}