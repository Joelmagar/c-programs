// Largest and smallest element in an array



#include <stdio.h>

int main () {
    int n;
    printf("Enter the count of array elements\n");
    scanf("%d",&n);
    int arr[n];
    for (int i = 0; i < n ; i++) {
        printf("Enter element %d\t:",i+1);
        scanf("%d",&arr[i]);
   
    }
    int largest=arr[0],smallest=arr[0];
    for (int i = 0; i < n; i++) {
     if(largest < arr[i]){
            largest= arr[i];
        }
        if(smallest > arr[i]){
            smallest= arr[i];
        }    }
    printf("largest is %d and smallest is %d\n",largest,smallest);
  

    return 0;
}