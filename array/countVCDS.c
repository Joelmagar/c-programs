// count Vowels,consonents,digits and spaces in an string

#include <stdio.h>
#include <ctype.h>  // for tolower() and isdigit()
#include <string.h>
int main() {
    char str[1000];
    int vowels = 0, consonants = 0, digits = 0, spaces = 0;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);  // safer than gets()
    str[strcspn(str, "\n")] = '\0';

    for (int i = 0; str[i] != '\0'; i++) {
        char ch = tolower(str[i]);  // convert to lowercase for easier comparison

        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            vowels++;
        } 
        else if ((ch >= 'a' && ch <= 'z')) {
            consonants++;
        } 
        else if (isdigit(ch)) {
            digits++;
        } 
        else if (ch == ' ' || ch == '\t' || ch == '\n') {
            spaces++;
        }
    }

    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    printf("Digits: %d\n", digits);
    printf("Spaces: %d\n", spaces);

    return 0;
}