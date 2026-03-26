// Check if the array is palindrome or not

#include <stdio.h>

int main () {
    int n,flag=1;
    printf("Enter the length of your array \n");
    scanf("%d",&n);
    int arr[n];
    for (int i = 0; i < n; i++) {
    printf("Enter the value of item %d\n",i+1);
    scanf("%d",&arr[i]);
}
for(int i =0;i<n/2;i++){
    if(arr[i] != arr[n -1 -i]){
        flag=0;
        break;
    }
}
if(flag==1){
    
    printf("The array is a palindrome.\n");
}
else{
        printf("The array is not a palindrome.\n");

    }
    return 0;
}