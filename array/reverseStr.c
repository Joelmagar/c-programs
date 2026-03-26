// Reverse string

#include <stdio.h>
#include <string.h>
int main () {

    char str[100];
    printf("Enter string\n");
    fgets(str,sizeof(str),stdin);
    str[strcspn(str, "\n")] = '\0';
    int len= strlen(str);
    printf("Reverse is :");
    
    for(int i=0;i<len/2 ;i++){
        char temp = str[i];
        str[i]=str[len - 1- i];
        str[len -1 -i]=temp;
    }
    printf("%s",str);

    return 0;
}