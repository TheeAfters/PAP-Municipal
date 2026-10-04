#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "budget.h"

static char   deptName[MAX_DEPARTMENTS][NAME_LEN];
static double allocated[MAX_DEPARTMENTS];
static double expenditure[MAX_DEPARTMENTS];
static int    deptCount = 0;

static void readLine(const char *prompt, char *buf, int size)
{
    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
}

static int isBlank(const char *s)
{
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isspace((unsigned char)s[i])) {
            return 0;
        }
    }
    return 1;
}

static double readAmount(const char *prompt)
{
    char line[64];
    char *end;
    double value;

    while (1) {
        readLine(prompt, line, sizeof(line));
        if (isBlank(line)) {
            printf("Error: amount cannot be empty.\n");
            continue;
        }
        value = strtod(line, &end);
        while (isspace((unsigned char)*end)) end++;
        if (*end != '\0') {
            printf("Error: '%s' is not a valid number.\n", line);
        } else if (value < 0) {
            printf("Error: amount cannot be negative.\n");
        } else {
            return value;
        }
    }
}

static void readDepartmentName(char *name)
{
    while (1) {
        readLine("Department name: ", name, NAME_LEN);
        if (isBlank(name)) {
            printf("Error: department name cannot be empty.\n");
        } else {
            return;
        }
    }
}

double calculateRemaining(double allocatedAmt, double spent)
{
    return allocatedAmt - spent;
}

const char *getBudgetStatus(double allocatedAmt, double spent)
{
    if (spent > allocatedAmt) {
        return "OVER BUDGET";
    }
    return "WITHIN BUDGET";
}

int findDepartment(const char *name)
{
    for (int i = 0; i < deptCount; i++) {
        if (strcmp(deptName[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

void addDepartmentBudget(void)
{
    char name[NAME_LEN];

    if (deptCount >= MAX_DEPARTMENTS) {
        printf("Error: department list is full (%d max).\n", MAX_DEPARTMENTS);
        return;
    }

    readDepartmentName(name);

    if (findDepartment(name) != -1) {
        printf("Error: '%s' already has a budget.\n", name);
        return;
    }

    double amount = readAmount("Allocated budget (N$): ");

    strcpy(deptName[deptCount], name);
    allocated[deptCount] = amount;
    expenditure[deptCount] = 0.0;
    deptCount++;

    printf("Budget of N$%.2f added for %s.\n", amount, name);
}

void enterExpenditure(void)
{
    char name[NAME_LEN];

    if (deptCount == 0) {
        printf("No departments yet. Add a department budget first.\n");
        return;
    }

    readDepartmentName(name);
    int idx = findDepartment(name);
    if (idx == -1) {
        printf("Error: department '%s' not found.\n", name);
        return;
    }

    double amount = readAmount("Expenditure to add (N$): ");
    expenditure[idx] += amount;

    printf("Total expenditure for %s is now N$%.2f.\n", deptName[idx], expenditure[idx]);
    if (expenditure[idx] > allocated[idx]) {
        printf("WARNING: %s has exceeded its budget by N$%.2f!\n",
               deptName[idx], expenditure[idx] - allocated[idx]);
    }
}

void displayBudgets(void)
{
    if (deptCount == 0) {
        printf("No budget information to display.\n");
        return;
    }

    printf("\n%-20s %14s %14s %14s  %s\n",
           "Department", "Allocated", "Expenditure", "Remaining", "Status");
    printf("-----------------------------------------------------------------------------\n");
    for (int i = 0; i < deptCount; i++) {
        double remaining = calculateRemaining(allocated[i], expenditure[i]);
        printf("%-20s %14.2f %14.2f %14.2f  %s\n",
               deptName[i], allocated[i], expenditure[i], remaining,
               getBudgetStatus(allocated[i], expenditure[i]));
    }
}

void showExceededDepartments(void)
{
    int found = 0;

    printf("\nDepartments that exceeded their budget:\n");
    for (int i = 0; i < deptCount; i++) {
        if (expenditure[i] > allocated[i]) {
            printf("  - %s (over by N$%.2f)\n",
                   deptName[i], expenditure[i] - allocated[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("  None. All departments are within budget.\n");
    }
}

int getDepartmentCount(void)
{
    return deptCount;
}

double getTotalAllocated(void)
{
    double total = 0.0;
    for (int i = 0; i < deptCount; i++) {
        total += allocated[i];
    }
    return total;
}

double getTotalExpenditure(void)
{
    double total = 0.0;
    for (int i = 0; i < deptCount; i++) {
        total += expenditure[i];
    }
    return total;
}

void displayBudgetReport(void)
{
    printf("\n===== BUDGET REPORT =====\n");
    if (deptCount == 0) {
        printf("No budget data available.\n");
        return;
    }
    double totalAlloc = getTotalAllocated();
    double totalSpent = getTotalExpenditure();

    printf("Departments:         %d\n", deptCount);
    printf("Total Allocated:     N$%.2f\n", totalAlloc);
    printf("Total Expenditure:   N$%.2f\n", totalSpent);
    printf("Remaining Budget:    N$%.2f\n", calculateRemaining(totalAlloc, totalSpent));
    showExceededDepartments();
}

void budgetMenu(void)
{
    char line[16];
    int choice;

    do {
        printf("\n========== BUDGET MANAGEMENT ==========\n");
        printf("1. Add department budget\n");
        printf("2. Enter expenditure\n");
        printf("3. Display all budgets\n");
        printf("4. Show departments over budget\n");
        printf("5. Back to main menu\n");
        readLine("Enter your choice: ", line, sizeof(line));

        char *end;
        choice = (int)strtol(line, &end, 10);
        if (end == line || *end != '\0') {
            choice = 0;
        }

        switch (choice) {
            case 1: addDepartmentBudget();     break;
            case 2: enterExpenditure();        break;
            case 3: displayBudgets();          break;
            case 4: showExceededDepartments(); break;
            case 5: break;
            default: printf("Invalid choice. Enter a number from 1 to 5.\n");
        }
    } while (choice != 5);
}
