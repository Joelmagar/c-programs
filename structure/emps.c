#include <stdio.h>
#include <string.h>

#define MAX 100

struct Employee {
    int id;
    char name[50];
    float salary;
};

struct Employee emp[MAX];
int count = 0;

// Function to add employee
void addEmployee() {
    if (count >= MAX) {
        printf("\nEmployee list is full!\n");
        return;
    }

    printf("\nEnter Employee ID: ");
    scanf("%d", &emp[count].id);

    printf("Enter Employee Name: ");
    scanf(" %[^\n]", emp[count].name);

    printf("Enter Salary: ");
    scanf("%f", &emp[count].salary);

    count++;
    printf("\nEmployee added successfully!\n");
}

// Function to display all employees
void displayEmployees() {
    if (count == 0) {
        printf("\nNo employees to display.\n");
        return;
    }

    printf("\n--- Employee List ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. ID: %d | Name: %s | Salary: %.2f\n",
               i + 1, emp[i].id, emp[i].name, emp[i].salary);
    }
}

// Function to search employee
void searchEmployee() {
    char searchName[50];
    int found = 0;

    printf("\nEnter name to search: ");
    scanf(" %[^\n]", searchName);

    for (int i = 0; i < count; i++) {
        if (strcmp(emp[i].name, searchName) == 0) {
            printf("\nEmployee Found!\n");
            printf("ID: %d | Name: %s | Salary: %.2f\n",
                   emp[i].id, emp[i].name, emp[i].salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nEmployee not found.\n");
    }
}

// Function to delete employee
void deleteEmployee() {
    if (count == 0) {
        printf("\nNo employees to delete.\n");
        return;
    }

    displayEmployees();

    int choice;
    printf("\nEnter employee number to delete: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > count) {
        printf("\nInvalid selection!\n");
        return;
    }

    char confirm;
    printf("Are you sure you want to delete %s? (y/n): ", emp[choice - 1].name);
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = choice - 1; i < count - 1; i++) {
            emp[i] = emp[i + 1];
        }
        count--;
        printf("\nEmployee deleted successfully!\n");
    } else {
        printf("\nDeletion cancelled.\n");
    }
}

// Main function
int main() {
    int option;

    do {
        printf("\n====== Employee Management System ======\n");
        printf("1. Add New Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Delete Employee\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                deleteEmployee();
                break;
            case 0:
                printf("\nExiting program...\n");
                break;
            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (option != 0);

    return 0;
}