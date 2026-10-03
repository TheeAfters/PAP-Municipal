#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 20
#define NAME_LEN 50

void budgetMenu(void);

void addDepartmentBudget(void);
void enterExpenditure(void);
void displayBudgets(void);
void showExceededDepartments(void);

double calculateRemaining(double allocated, double spent);
const char *getBudgetStatus(double allocated, double spent);

int findDepartment(const char *name);

int    getDepartmentCount(void);
double getTotalAllocated(void);
double getTotalExpenditure(void);
void   displayBudgetReport(void);

#endif
