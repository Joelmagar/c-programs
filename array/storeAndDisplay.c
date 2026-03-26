// Get input array and display it

#include <stdio.h>

int main () {
    int n,arr[n];
printf("Enter the count of array elements\n");
scanf("%d",&n);
for (int i = 0; i < n ; i++) {
    printf("Enter element %d\t",i+1);
    scanf("%d",&arr[i]);
}
printf("Array elements are:\n");
for (int i = 0; i < n ; i++) {
    printf("%d",arr[i]);
    
}

    return 0;
}