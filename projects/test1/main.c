#include <stdio.h>
#include <stdlib.h>
#include<string.h>
struct employee {
    int id;
    char name[50];
    float salary;
};
int main() {
    int choice;
    while (1) {
        printf("1. Add new employee\n");
        printf("2,Display Employees\n");
        printf("3.Search Employees\n");
        printf("4. Delete new employee\n");
        printf("0. Exit\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);
        if (choice == 0)
            break;

    
    FILE*fp;
    fp=fopen("employees.dat","ab+");
    struct employee emp;
    if (choice == 1) {
        printf("Enter ID name salary:");
        scanf("%d %s %f",&emp.id,emp.name,&emp.salary);
        fwrite(&emp,sizeof(struct employee),1,fp);
        printf("Employee added successfully\n");
    }
    else if (choice == 2) {
        rewind(fp);
        while (fread(&emp,sizeof(struct employee),1,fp)) {
            printf("\nID: %d",emp.id);
            printf("\nName: %s",emp.name);
            printf("\nSalary: %.2f",emp.salary);
        }
    }
else if (choice == 3) {
    int id,found=0;
    printf("Enter ID to search:");
    scanf("%d",&id);
    rewind(fp);
    while (fread(&emp,sizeof(struct employee),1,fp)) {
        if (emp.id == id)
        {
            printf("found:%s %.2f",emp.name,emp.salary);
            found=1;
        }
    }
    if (!found){
        printf("No such employee found\n");
    }
}
    else if (choice == 4) {
        int id,found=0;
        FILE*temp=fopen("temp.dat","wb");
        printf("Enter ID to delete:");
        scanf("%d",&id);
        rewind(fp);
        while (fread(&emp,sizeof(struct employee),1,fp)) {
            if (emp.id == id)
                found=1;
            else
                fwrite(&emp,sizeof(struct employee),1,temp);
        }
        fclose(temp);
        fclose(fp);
        remove("employees.dat");
        rename("temp.dat","employees.dat");
        fp=fopen("employees.dat","ab+");
        if (found) {
            printf("Employee deleted successfully\n");
        }
        else {
            printf("No such employee found\n");
        }
    }

    fclose(fp);
}
    return 0;
}

