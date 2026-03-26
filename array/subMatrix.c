// Subtract two matrix


#include<stdio.h>


void loopFuction(int rowLen,int colLen, int arr[rowLen][colLen]);
void subFunction(int rowLen,int colLen, int arr1[rowLen][colLen], int arr2[rowLen][colLen],int sub[rowLen][colLen]);


int main(){
    int rowLen=0,colLen=0;
    printf("Enter the size of row :");
    scanf("%d",&rowLen);
    printf("Enter the size of column :");
    scanf("%d",&colLen);
    if(rowLen <= 0 || colLen <= 0){
    printf("Invalid matrix size\n");
    return 1;
}

    int arr1[rowLen][colLen];
    int arr2[rowLen][colLen];
    printf("Enter the values of first Array \n");
    loopFuction(rowLen,colLen,arr1);
    printf("Enter the values of second Array \n");
    loopFuction(rowLen,colLen,arr2);
    int sub[rowLen][colLen];
    subFunction(rowLen,colLen,arr1,arr2,sub);
    
    for(int i =0;i<rowLen;i++){
    for(int j =0;j<colLen;j++){
    printf("%d  ",sub[i][j]);
    }
    printf("\n");

    }



    return 0;
}

void loopFuction(int rowLen,int colLen, int arr[rowLen][colLen]){
    for(int i =0;i<rowLen;i++){
    for(int j =0;j<colLen;j++){
    printf("Enter the value of item row:%d column:%d\t",i+1,j+1);
    scanf("%d",&arr[i][j]);
    }}
}

void subFunction( int rowLen,int colLen, int arr1[rowLen][colLen], int arr2[rowLen][colLen],int sub[rowLen][colLen]){
    for(int i =0;i<rowLen;i++){
    for(int j =0;j<colLen;j++){
    sub[i][j] = arr1[i][j] - arr2[i][j];
    }}
}
