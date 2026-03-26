// Find second largest in the given array.
#include <stdio.h>

int main () {
    int n;
    printf("Enter the length of your array\n");
    scanf("%d",&n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        printf("Enter element %d\t",i+1);
        scanf("%d",&arr[i]);
    }
    for(int i =0; i<n;i++){
        for(int j=1+i;j<=n;j++){
            if(arr[j] > arr[i]){
                int swapper= arr[i];
                arr[i]=arr[j];
                arr[j]=swapper;
            }
        }
    }

    printf("The second largest is %d\n",arr[2]);


    return 0;
}