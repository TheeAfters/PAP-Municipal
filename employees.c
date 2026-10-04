#include <stdio.h>
#include <string.h>
#include "employees.h"

void addEmployee(Employee employees[], int *count)
{
    Employee *e;

    if (*count >= MAX_EMPLOYEES)
    {
        printf("Employee list is full.\n");
        return;
    }

    e = &employees[*count];

    printf("\n========== ADD EMPLOYEE ==========\n");

    printf("Enter Employee ID: ");
    scanf("%d", &e->employeeID);

    while (getchar() != '\n');

    printf("Enter employee name: ");
    fgets(e->name, sizeof(e->name), stdin);
    e->name[strcspn(e->name, "\n")] = '\0';

    if (strlen(e->name) == 0)
    {
        printf("Employee name cannot be empty.\n");
        return;
    }

    printf("Enter department: ");
    fgets(e->department, sizeof(e->department), stdin);
    e->department[strcspn(e->department, "\n")] = '\0';

    printf("Enter basic salary: ");
    scanf("%lf", &e->basicSalary);

    printf("Enter housing allowance: ");
    scanf("%lf", &e->housingAllowance);

    printf("Enter transport allowance: ");
    scanf("%lf", &e->transportAllowance);

    (*count)++;

    printf("\nEmployee added successfully!\n");
}

void displayEmployees(const Employee employees[], int count)
{
    int i;

    if (count == 0)
    {
        printf("\nNo employees registered.\n");
        return;
    }

    printf("\n========== EMPLOYEE LIST ==========\n");

    for (i = 0; i < count; i++)
    {
        printf("\nEmployee ID: %d\n", employees[i].employeeID);
        printf("Name: %s\n", employees[i].name);
        printf("Department: %s\n", employees[i].department);
        printf("Basic Salary: N$%.2f\n", employees[i].basicSalary);
        printf("Housing Allowance: N$%.2f\n", employees[i].housingAllowance);
        printf("Transport Allowance: N$%.2f\n",
               employees[i].transportAllowance);
        printf("Total Salary: N$%.2f\n",
               calculateSalary(&employees[i]));
    }
}

int searchEmployee(const Employee employees[], int count, int employeeID)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (employees[i].employeeID == employeeID)
        {
            return i;
        }
    }

    return -1;
}

double calculateSalary(const Employee *employee)
{
    return employee->basicSalary
         + employee->housingAllowance
         + employee->transportAllowance;
}

void employeeMenu(Employee employees[], int *count)
{
    int choice;
    int employeeID;
    int result;

    do
    {
        printf("\n====================================\n");
        printf("        EMPLOYEE MANAGEMENT\n");
        printf("====================================\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Return to Main Menu\n");
        printf("====================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addEmployee(employees, count);
                break;

            case 2:
                displayEmployees(employees, *count);
                break;

            case 3:
                printf("Enter Employee ID to search: ");
                scanf("%d", &employeeID);

                result = searchEmployee(employees, *count, employeeID);

                if (result == -1)
                {
                    printf("Employee not found.\n");
                }
                else
                {
                    printf("\nEmployee found!\n");
                    printf("ID: %d\n", employees[result].employeeID);
                    printf("Name: %s\n", employees[result].name);
                    printf("Department: %s\n",
                           employees[result].department);
                }
                break;

            case 4:
                break;

            default:
                printf("Invalid choice.\n");
        }

        } while (choice != 4);
}