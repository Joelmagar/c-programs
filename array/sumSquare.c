// sum of square of array elements

#include <stdio.h>

int main () {
    int n,sum=0;
    printf("Enter the count of array elements\n");
    scanf("%d",&n);
    int arr[n];
    for (int i = 0; i < n ; i++) {
        printf("Enter element %d\t:",i+1);
        scanf("%d",&arr[i]);
        sum+=arr[i] * arr[i];
}
    printf("Sum of square of array element is  %d",sum);
    return 0;
}