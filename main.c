#include <stdio.h>
#include "utils.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

static Employee employees[MAX_EMPLOYEES];
static int employeeCount = 0;

static void supplierMenu(void)
{
    int choice;
    do {
        printf("\n========== SUPPLIER MANAGEMENT ==========\n1. Add supplier\n2. Display suppliers\n3. Search supplier\n4. Back\n");
        choice = readInt("Enter your choice: ", 1, 4);
        if (choice == 1) addSupplier();
        else if (choice == 2) displaySuppliers();
        else if (choice == 3) searchSupplier();
    } while (choice != 4);
}

static void assetMenu(void)
{
    int choice;
    do {
        printf("\n========== ASSET MANAGEMENT ==========\n1. Add asset\n2. Display assets\n3. Search asset\n4. Back\n");
        choice = readInt("Enter your choice: ", 1, 4);
        if (choice == 1) addAsset();
        else if (choice == 2) displayAssets();
        else if (choice == 3) searchAsset();
    } while (choice != 4);
}

static void reportsMenu(void)
{
    int choice;
    do {
        printf("\n========== REPORTS ==========\n1. Employee report\n2. Budget report\n3. Supplier report\n4. Asset report\n5. Back\n");
        choice = readInt("Enter your choice: ", 1, 5);
        switch (choice) {
            case 1: {
                if (employeeCount == 0) { printf("No employee data available.\n"); break; }
                double total = 0, high = calculateSalary(&employees[0]), low = high;
                for (int i = 0; i < employeeCount; i++) {
                    double s = calculateSalary(&employees[i]);
                    total += s; if (s > high) high = s; if (s < low) low = s;
                }
                printf("\nEmployee Report\nEmployees: %d\nAverage Gross Salary: N$%.2f\nHighest Gross Salary: N$%.2f\nLowest Gross Salary: N$%.2f\n", employeeCount, total / employeeCount, high, low);
                break;
            }
            case 2: displayBudgetReport(); break;
            case 3: printf("\nSupplier Report\nSuppliers: %d\n", supplierCount); displaySuppliers(); break;
            case 4: {
                double total = 0; for (int i = 0; i < assetCount; i++) total += assets[i].purchaseValue;
                printf("\nAsset Report\nAssets: %d\nTotal Purchase Value: N$%.2f\n", assetCount, total); displayAssets(); break;
            }
        }
    } while (choice != 5);
}

int main(void)
{
    int choice;
    do {
        printf("\n===============================================\n");
        printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM (MFMS)\n");
        printf("===============================================\n");
        printf("1. Employee Management\n2. Budget Management\n3. Supplier Management\n4. Asset Management\n5. Reports\n6. Exit\n");
        choice = readInt("Enter your choice: ", 1, 6);
        switch (choice) {
            case 1: employeeMenu(employees, &employeeCount); break;
            case 2: budgetMenu(); break;
            case 3: supplierMenu(); break;
            case 4: assetMenu(); break;
            case 5: reportsMenu(); break;
            case 6: printf("Goodbye.\n"); break;
        }
    } while (choice != 6);
    return 0;
}
