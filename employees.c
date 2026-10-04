#include <stdio.h>
#include "employees.h"
#include "utils.h"

static int employeeIdExists(const Employee employees[], int count, int id)
{
    return searchEmployee(employees, count, id) != -1;
}

void addEmployee(Employee employees[], int *count)
{
    if (*count >= MAX_EMPLOYEES) { printf("Employee list is full.\n"); return; }
    Employee *e = &employees[*count];
    printf("\n========== ADD EMPLOYEE ==========\n");
    while (1) {
        e->employeeID = readInt("Enter Employee ID: ", 1, 2147483647);
        if (employeeIdExists(employees, *count, e->employeeID)) printf("That Employee ID already exists.\n");
        else break;
    }
    readString("Enter employee name: ", e->name, sizeof(e->name));
    readString("Enter department: ", e->department, sizeof(e->department));
    e->basicSalary = readDouble("Enter basic salary (N$): ", 0.0);
    e->housingAllowance = readDouble("Enter housing allowance (N$): ", 0.0);
    e->transportAllowance = readDouble("Enter transport allowance (N$): ", 0.0);
    (*count)++;
    printf("Employee added successfully!\n");
}

void displayEmployees(const Employee employees[], int count)
{
    if (count == 0) { printf("\nNo employees registered.\n"); return; }
    printf("\n================ EMPLOYEE LIST ================\n");
    for (int i = 0; i < count; i++) {
        printf("\nEmployee ID: %d\nName: %s\nDepartment: %s\n", employees[i].employeeID, employees[i].name, employees[i].department);
        printf("Basic Salary: N$%.2f\nHousing Allowance: N$%.2f\nTransport Allowance: N$%.2f\n", employees[i].basicSalary, employees[i].housingAllowance, employees[i].transportAllowance);
        printf("Gross Salary: N$%.2f\n", calculateSalary(&employees[i]));
    }
}

int searchEmployee(const Employee employees[], int count, int employeeID)
{
    for (int i = 0; i < count; i++) if (employees[i].employeeID == employeeID) return i;
    return -1;
}

double calculateSalary(const Employee *employee)
{
    if (employee == NULL) return 0.0;
    return employee->basicSalary + employee->housingAllowance + employee->transportAllowance;
}

void employeeMenu(Employee employees[], int *count)
{
    int choice;
    do {
        printf("\n====================================\n        EMPLOYEE MANAGEMENT\n====================================\n1. Add Employee\n2. Display Employees\n3. Search Employee\n4. Return to Main Menu\n====================================\n");
        choice = readInt("Enter your choice: ", 1, 4);
        switch (choice) {
            case 1: addEmployee(employees, count); break;
            case 2: displayEmployees(employees, *count); break;
            case 3: {
                int id = readInt("Enter Employee ID to search: ", 1, 2147483647);
                int result = searchEmployee(employees, *count, id);
                if (result == -1) printf("Employee not found.\n");
                else {
                    printf("\nEmployee found!\nID: %d\nName: %s\nDepartment: %s\nGross Salary: N$%.2f\n", employees[result].employeeID, employees[result].name, employees[result].department, calculateSalary(&employees[result]));
                }
                break;
            }
            case 4: break;
        }
    } while (choice != 4);
}
