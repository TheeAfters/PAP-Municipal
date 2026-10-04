#include <stdio.h>
#include <string.h>
#include "suppliers.h"

static Supplier suppliers[MAX_SUPPLIERS];
static int supplierCount = 0;

int getSupplierCount(void)
{
    return supplierCount;
}

const Supplier *getSupplier(int index)
{
    if (index < 0 || index >= supplierCount) {
        return NULL;
    }
    return &suppliers[index];
}

static int findSupplierById(int id)
{
    int i;
    for (i = 0; i < supplierCount; i++) {
        if (suppliers[i].id == id) {
            return i;
        }
    }
    return -1;
}

void addSupplier(void)
{
    Supplier s;
    int id;
    printf("\n--- Add Supplier ---\n");
    if (supplierCount >= MAX_SUPPLIERS) {
        printf("  ! Supplier list is full (max %d).\n", MAX_SUPPLIERS);
        return;
    }
    id = readIntInRange("Enter Supplier ID (1-99999): ", 1, 99999);
    if (findSupplierById(id) != -1) {
        printf("  ! A supplier with ID %d already exists.\n", id);
        return;
    }
    s.id = id;
    readLine("Enter Supplier Name: ", s.name, NAME_LEN);
    readLine("Enter Email: ", s.email, EMAIL_LEN);
    readLine("Enter Telephone: ", s.telephone, PHONE_LEN);
    readLine("Enter Town/Location: ", s.town, SHORT_LEN);
    suppliers[supplierCount] = s;
    supplierCount++;
    printf("  > Supplier '%s' added successfully.\n", s.name);
}

void displaySuppliers(void)
{
    int i;
    printf("\n--- Supplier List (%d) ---\n", supplierCount);
    if (supplierCount == 0) {
        printf("  (no suppliers recorded yet)\n");
        return;
    }
    printf("%-6s %-20s %-24s %-14s %-14s\n",
           "ID", "Name", "Email", "Telephone", "Town");
    printf("------------------------------------------------------------------------------------\n");
    for (i = 0; i < supplierCount; i++) {
        printf("%-6d %-20s %-24s %-14s %-14s\n",
               suppliers[i].id, suppliers[i].name, suppliers[i].email,
               suppliers[i].telephone, suppliers[i].town);
    }
}

void searchSupplier(void)
{
    int choice;
    printf("\n--- Search Supplier ---\n");
    if (supplierCount == 0) {
        printf("  (no suppliers to search)\n");
        return;
    }
    printf("1. Search by ID\n2. Search by Town/Location\n");
    choice = readIntInRange("Choose search type: ", 1, 2);

    if (choice == 1) {
        int id = readIntInRange("Enter Supplier ID: ", 1, 99999);
        int idx = findSupplierById(id);
        if (idx == -1) {
            printf("  ! No supplier found with ID %d.\n", id);
            return;
        }
        printf("  > Found: %s | %s | %s | %s\n",
               suppliers[idx].name, suppliers[idx].email,
               suppliers[idx].telephone, suppliers[idx].town);
    } else {
        char town[SHORT_LEN];
        int i, found = 0;
        readLine("Enter Town/Location: ", town, SHORT_LEN);
        for (i = 0; i < supplierCount; i++) {
            if (strcmp(suppliers[i].town, town) == 0) {
                printf("  > %s (ID %d), %s, %s\n",
                       suppliers[i].name, suppliers[i].id,
                       suppliers[i].email, suppliers[i].telephone);
                found = 1;
            }
        }
        if (!found) {
            printf("  ! No suppliers located in '%s'.\n", town);
        }
    }
}

void supplierMenu(void)
{
    int choice;
    do {
        printf("\n===== SUPPLIER MANAGEMENT =====\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back to Main Menu\n");
        choice = readIntInRange("Enter your choice: ", 1, 4);
        switch (choice) {
            case 1: addSupplier();      break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier();   break;
            case 4: return;
        }
        if (choice != 4) {
            pauseScreen();
        }
    } while (choice != 4);
}
