// Find  a person whose height is greater than 170cm  and weight is less  than  60 kg  from given data

#include <stdio.h>

int main () {

    float height,weight;
    int count=0,length;

    printf("Enter total number of people\n");
    scanf("%d",&length);

    for(int i =0;i<length;i++){

        printf("Enter height in cm\n");
        scanf("%f",&height);
        printf("Enter weight in kg\n");
        scanf("%f",&weight);
        if(height > 170.00 && weight < 60.00){
            ++count;
        }
    }
    printf("Total number of people with height is greater than 170cm  and weight is less  than  60 kg are %d\n",count );
        
    
    return 0;
}