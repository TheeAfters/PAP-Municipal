#include <stdio.h>
#include <stdlib.h>
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static int readMenuChoice(void) {
    int choice;
    while (1) {
        printf("Enter your choice: ");
        if (scanf("%d", &choice) == 1) {
            clearInputBuffer();
            return choice;
        }
        printf("Invalid input. Please enter a number.\n");
        clearInputBuffer();
    }
}

static void displayMenu(void) {
    printf("\n========================================\n");
    printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
    printf("========================================\n");
}

static void employeeMenu(void) {
    int choice;
    do {
        printf("\n--- Employee Management ---\n");
        printf("1. Add employee\n");
        printf("2. Display employees\n");
        printf("3. Search employee\n");
        printf("4. Calculate/display salary\n");
        printf("5. Back to main menu\n");
        choice = readMenuChoice();

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: calculateEmployeeSalary(); break;
            case 5: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
}

static void budgetMenu(void) {
    int choice;
    do {
        printf("\n--- Budget Management ---\n");
        printf("1. Add/enter departmental budget\n");
        printf("2. Display budgets\n");
        printf("3. Search department budget\n");
        printf("4. Back to main menu\n");
        choice = readMenuChoice();

        switch (choice) {
            case 1: addBudget(); break;
            case 2: displayBudgets(); break;
            case 3: searchBudget(); break;
            case 4: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}

static void supplierMenu(void) {
    int choice;
    do {
        printf("\n--- Supplier Management ---\n");
        printf("1. Add supplier\n");
        printf("2. Display suppliers\n");
        printf("3. Search supplier\n");
        printf("4. Back to main menu\n");
        choice = readMenuChoice();

        switch (choice) {
            case 1: addSupplier(); break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier(); break;
            case 4: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}

static void assetMenu(void) {
    int choice;
    do {
        printf("\n--- Asset Management ---\n");
        printf("1. Add asset\n");
        printf("2. Display assets\n");
        printf("3. Search asset\n");
        printf("4. Back to main menu\n");
        choice = readMenuChoice();

        switch (choice) {
            case 1: addAsset(); break;
            case 2: displayAssets(); break;
            case 3: searchAsset(); break;
            case 4: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}

static void reportMenu(void) {
    int choice;
    do {
        printf("\n--- Reports ---\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Full Report\n");
        printf("6. Back to main menu\n");
        choice = readMenuChoice();

        switch (choice) {
            case 1: employeeReport(); break;
            case 2: budgetReport(); break;
            case 3: supplierReport(); break;
            case 4: assetReport(); break;
            case 5: fullReport(); break;
            case 6: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);
}

int main(void) {
    int choice;

    printf("Welcome to the Municipal Financial Management System.\n");

    do {
        displayMenu();
        choice = readMenuChoice();

        switch (choice) {
            case 1: employeeMenu(); break;
            case 2: budgetMenu(); break;
            case 3: supplierMenu(); break;
            case 4: assetMenu(); break;
            case 5: reportMenu(); break;
            case 6:
                printf("Thank you for using MFMS. Goodbye!\n");
                break;
            default:
                printf("Invalid menu choice. Please select 1-6.\n");
        }
    } while (choice != 6);

    return 0;
}
