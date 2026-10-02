#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100

typedef struct {
    int id;
    char name[60];
    char email[80];
    char telephone[30];
    char town[50];
} Supplier;

extern Supplier suppliers[MAX_SUPPLIERS];
extern int supplierCount;

void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);

#endif
