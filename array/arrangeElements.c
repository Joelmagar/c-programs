// Arrange array elements in ascending order and descending order


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

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n ; j++) {
        if(arr[i] > arr[j]){
           int swap = arr[i];
           arr[i] =arr[j];
           arr[j]=swap;
        }
    }

    }
    printf("Array in Ascending order:\t");
    for (int i = 0; i < n ; i++) {
        printf("%d",arr[i]);
    }
    printf("\nArray in Descending order:\t");
    for (int i = n-1; i >=0 ; i--) {
        printf("%d",arr[i]);
    }

    return 0;
}