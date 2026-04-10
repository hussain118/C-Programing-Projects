#include <stdio.h>
#include <string.h>

#define MAXEMPLOYEES 50

struct employee {
    char name[50];
    int salary;
    int id;
    char designation[50];
};


void inputEmployees(struct employee e[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter name of employee %d: ", i + 1);
        getchar();  
        fgets(e[i].name, 50, stdin);
        e[i].name[strcspn(e[i].name, "\n")] = '\0';        

        printf("Enter salary of employee %d: ", i + 1);
        scanf("%d", &e[i].salary);

        printf("Enter ID of employee %d: ", i + 1);
        scanf("%d", &e[i].id);

        printf("Enter designation of employee %d: ", i + 1);
        getchar();  
        fgets(e[i].designation, 50, stdin);
        e[i].designation[strcspn(e[i].designation, "\n")] = '\0';
    }
}


void displayEmployees(struct employee e[], int n) {
    printf("\n%-5s %-20s %-10s %-20s\n", "ID", "Name", "Salary", "Designation");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-5d %-20s %-10d %-20s\n", e[i].id, e[i].name, e[i].salary, e[i].designation);
    }
}


void findHighestSalary(struct employee e[], int n) {
    if (n == 0) return;

    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (e[i].salary > e[maxIndex].salary)
            maxIndex = i;
    }

    printf("\nEmployee with highest salary:\n");
    printf("%-5s %-20s %-10s %-20s\n", "ID", "Name", "Salary", "Designation");
    printf("-----------------------------------------------------------\n");
    printf("%-5d %-20s %-10d %-20s\n", e[maxIndex].id, e[maxIndex].name, e[maxIndex].salary, e[maxIndex].designation);
}

void searchEmployee(struct employee e[], int n) {
    int choice;
    printf("\nSearch by:\n1. ID\n2. Name\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int searchID;
        printf("Enter ID to search: ");
        scanf("%d", &searchID);

        for (int i = 0; i < n; i++) {
            if (e[i].id == searchID) {
                printf("Employee found: %s, Salary: %d, Designation: %s\n", e[i].name, e[i].salary, e[i].designation);
                return;
            }
        }
        printf("No employee found with ID %d\n", searchID);
    } else if (choice == 2) {
        char searchName[50];
        printf("Enter Name to search: ");
        getchar(); 
        fgets(searchName, 50, stdin);
        searchName[strcspn(searchName, "\n")] = '\0';

        for (int i = 0; i < n; i++) {
            if (strcmp(e[i].name, searchName) == 0) {
                printf("Employee found: ID: %d, Salary: %d, Designation: %s\n", e[i].id, e[i].salary, e[i].designation);
                return;
            }
        }
        printf("No employee found with Name %s\n", searchName);
    } else {
        printf("Invalid choice\n");
    }
}

void applyBonus(struct employee e[], int n, int threshold) {
    for (int i = 0; i < n; i++) {
        if (e[i].salary < threshold) {
            e[i].salary = e[i].salary * 1.1;
        }
    }
}

int main() {
    int n;
    struct employee employees[MAXEMPLOYEES];

    printf("Enter number of employees: ");
    scanf("%d", &n);

    inputEmployees(employees, n);
    displayEmployees(employees, n);
    findHighestSalary(employees, n);
    searchEmployee(employees, n);

    int bonusThreshold = 50000;
    applyBonus(employees, n, bonusThreshold);

    printf("\nAfter applying bonus to employees earning less than %d:\n", bonusThreshold);
    displayEmployees(employees, n);

    return 0;
}


