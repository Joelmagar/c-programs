// Reverse array elements 


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

    // extra array
    // for (int i = 0; i <n ; i++) {
    //     rev[i]= arr[n-1-i];
    // }

    // With out creating extra array
    for (int i = 0; i < n/2; i++) {
        int temp = arr[i];
        arr[i] = arr[n-1-i];
        arr[n-1-i] = temp;
    }
    
    printf("\nAReversed array:\t");
    for (int i =0; i<n ; i++) {
      
        printf("%d",arr[i]);
    }

    return 0;
}