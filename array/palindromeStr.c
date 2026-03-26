// Check if the string is palindrome or not


// reversing and comparing
#include <stdio.h>
#include <string.h>
int main () {
    char str[100];
    char copyStr[100];
    printf("Enter your string");
    scanf("%s",str);
    int len = strlen(str);
    strcpy(copyStr, str);

    for(int i = 0; i < len/2; i++) {
    char swapper= str[i];
    str[i]=str[len-1-i];
    str[len-1-i]=swapper;
    }
    if(strcmp(str,copyStr) == 0){
        printf("The string is a palindrome.\n");
    }else{
        printf("The string is not a palindrome.");
    }
    return 0;

}


// without reversing , comparing the ends
#include <stdio.h>
#include <string.h>
int main () {
    char str[100];
    int flag =1;
    printf("Enter your string\t");
    scanf("%s",str);
    int len = strlen(str);

    for(int i = 0; i < len/2; i++) {
        if(str[i]!=str[len-1-i]){
        flag =0;
        break;
        }
    }
    if(flag ==1){
        printf("The string is a palindrome.\n");
    }else{
        printf("The string is not a palindrome.");
    }
    return 0;

}
