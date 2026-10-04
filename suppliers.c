#include <stdio.h>
#include "suppliers.h"
#include "utils.h"

Supplier suppliers[MAX_SUPPLIERS];
int supplierCount = 0;

static int supplierIdExists(int id)
{
    for (int i = 0; i < supplierCount; i++) if (suppliers[i].id == id) return 1;
    return 0;
}

void addSupplier(void)
{
    if (supplierCount >= MAX_SUPPLIERS) { printf("Supplier storage is full.\n"); return; }
    int id;
    while (1) {
        id = readInt("Enter supplier ID: ", 1, 2147483647);
        if (supplierIdExists(id)) printf("That supplier ID already exists.\n"); else break;
    }
    suppliers[supplierCount].id = id;
    readString("Enter supplier name: ", suppliers[supplierCount].name, sizeof(suppliers[supplierCount].name));
    readString("Enter supplier email: ", suppliers[supplierCount].email, sizeof(suppliers[supplierCount].email));
    readString("Enter telephone number: ", suppliers[supplierCount].telephone, sizeof(suppliers[supplierCount].telephone));
    readString("Enter town/location: ", suppliers[supplierCount].town, sizeof(suppliers[supplierCount].town));
    supplierCount++;
    printf("Supplier added successfully.\n");
}

void displaySuppliers(void)
{
    if (supplierCount == 0) { printf("No suppliers registered.\n"); return; }
    printf("\n%-6s %-22s %-30s %-18s %-18s\n", "ID", "Name", "Email", "Telephone", "Town");
    printLine('-', 100);
    for (int i = 0; i < supplierCount; i++) printf("%-6d %-22s %-30s %-18s %-18s\n", suppliers[i].id, suppliers[i].name, suppliers[i].email, suppliers[i].telephone, suppliers[i].town);
}

void searchSupplier(void)
{
    if (supplierCount == 0) { printf("No suppliers registered.\n"); return; }
    char search[60];
    readString("Enter supplier name to search: ", search, sizeof(search));
    for (int i = 0; i < supplierCount; i++) {
        if (containsIgnoreCase(suppliers[i].name, search)) {
            printf("\nSupplier found:\nID: %d\nName: %s\nEmail: %s\nTelephone: %s\nTown/Location: %s\n", suppliers[i].id, suppliers[i].name, suppliers[i].email, suppliers[i].telephone, suppliers[i].town);
            return;
        }
    }
    printf("Supplier not found.\n");
}
