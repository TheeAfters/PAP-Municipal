#include <stdio.h>
#include "reports.h"
#include "common.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

void employeeReport(void)
{
    int i, count;
    double gross, total = 0.0, highest, lowest;
    const Employee *e;

    printf("\n========== EMPLOYEE REPORT ==========\n");
    count = getEmployeeCount();
    if (count == 0) {
        printf("No employees recorded.\n");
        return;
    }
    e = getEmployee(0);
    highest = lowest = calculateGrossSalary(e);
    for (i = 0; i < count; i++) {
        e = getEmployee(i);
        gross = calculateGrossSalary(e);
        total += gross;
        if (gross > highest) highest = gross;
        if (gross < lowest)  lowest  = gross;
    }
    printf("Total Employees : %d\n", count);
    printf("Average Salary  : N$%.2f\n", total / count);
    printf("Highest Salary  : N$%.2f\n", highest);
    printf("Lowest Salary   : N$%.2f\n", lowest);
}

void budgetReport(void)
{
    int i, count, exceeded = 0;
    double totalAllocated = 0.0, totalSpent = 0.0, remaining;
    const Budget *b;

    printf("\n========== BUDGET REPORT ==========\n");
    count = getBudgetCount();
    if (count == 0) {
        printf("No budgets recorded.\n");
        return;
    }
    for (i = 0; i < count; i++) {
        b = getBudget(i);
        totalAllocated += b->allocated;
        totalSpent     += b->expenditure;
        if (calculateRemaining(b) < 0.0) exceeded++;
    }
    remaining = totalAllocated - totalSpent;
    printf("Total Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalSpent);
    printf("Remaining Budget       : N$%.2f\n", remaining);
    printf("Departments Over Budget: %d\n", exceeded);
    if (exceeded > 0) {
        printf("  Over-budget departments:\n");
        for (i = 0; i < count; i++) {
            b = getBudget(i);
            if (calculateRemaining(b) < 0.0) {
                printf("   - %s (over by N$%.2f)\n",
                       b->department, -calculateRemaining(b));
            }
        }
    }
}

void supplierReport(void)
{
    int i, count;
    const Supplier *s;
    printf("\n========== SUPPLIER REPORT ==========\n");
    count = getSupplierCount();
    if (count == 0) {
        printf("No suppliers recorded.\n");
        return;
    }
    printf("Total Suppliers: %d\n", count);
    for (i = 0; i < count; i++) {
        s = getSupplier(i);
        printf("  - %s (ID %d), %s, %s\n", s->name, s->id, s->town, s->email);
    }
}

void assetReport(void)
{
    int i, count;
    double totalValue = 0.0;
    const Asset *a;
    printf("\n========== ASSET REPORT ==========\n");
    count = getAssetCount();
    if (count == 0) {
        printf("No assets recorded.\n");
        return;
    }
    printf("Total Assets: %d\n", count);
    for (i = 0; i < count; i++) {
        a = getAsset(i);
        totalValue += a->purchaseValue;
        printf("  - %s (%s), N$%.2f, %s [%s]\n",
               a->name, a->type, a->purchaseValue, a->department, a->condition);
    }
    printf("Total Asset Value: N$%.2f\n", totalValue);
}

void reportsMenu(void)
{
    int choice;
    do {
        printf("\n===== REPORTS =====\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");
        choice = readIntInRange("Enter your choice: ", 1, 5);
        switch (choice) {
            case 1: employeeReport(); break;
            case 2: budgetReport();   break;
            case 3: supplierReport(); break;
            case 4: assetReport();    break;
            case 5: return;
        }
        if (choice != 5) {
            pauseScreen();
        }
    } while (choice != 5);
}
