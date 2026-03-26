// Find Quatient and reminder of a n numbers divisible by 10

#include <stdio.h>

int main() {
    int qua, rem;
    int num, count = 0;

    printf("Enter your nth term:\n");
    scanf("%d", &num);

    for (int i = 1; count < num; i++) {
        if (i % 10 == 0) {
            qua = i / 10;
            rem = i % 10;
            count++;

            printf("Quotient = %d and Remainder = %d\n", qua, rem);
        }
    }

    return 0;
}