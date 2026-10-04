#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100

typedef struct
{
    int employeeID;
    char name[50];
    char department[50];
    double basicSalary;
    double housingAllowance;
    double transportAllowance;
} Employee;

void employeeMenu(Employee employees[], int *count);
void addEmployee(Employee employees[], int *count);
void displayEmployees(const Employee employees[], int count);
int searchEmployee(const Employee employees[], int count, int employeeID);
double calculateSalary(const Employee *employee);

#endif