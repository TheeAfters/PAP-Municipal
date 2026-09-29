#include <stdio.h>
#include <string.h>
#include "assets.h"

Asset assets[MAX_ASSETS];
int assetCount = 0;

static void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL)
        buffer[strcspn(buffer, "\n")] = '\0';
}

static void readRequiredString(const char *prompt, char *buffer, int size) {
    do {
        printf("%s", prompt);
        readLine(buffer, size);
        if (strlen(buffer) == 0) printf("Input cannot be empty.\n");
    } while (strlen(buffer) == 0);
}

static double readNonNegative(const char *prompt) {
    double value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &value) == 1 && value >= 0) {
            while (getchar() != '\n') {}
            return value;
        }
        printf("Enter a valid non-negative amount.\n");
        while (getchar() != '\n') {}
    }
}

void addAsset(void) {
    if (assetCount >= MAX_ASSETS) {
        printf("Asset storage is full.\n");
        return;
    }

    int id;
    printf("Enter asset ID: ");
    if (scanf("%d", &id) != 1 || id <= 0) {
        printf("Invalid asset ID.\n");
        while (getchar() != '\n') {}
        return;
    }
    while (getchar() != '\n') {}

    for (int i = 0; i < assetCount; i++) {
        if (assets[i].id == id) {
            printf("That asset ID already exists.\n");
            return;
        }
    }

    assets[assetCount].id = id;
    readRequiredString("Enter asset name: ", assets[assetCount].name,
                       sizeof(assets[assetCount].name));
    readRequiredString("Enter asset type: ", assets[assetCount].type,
                       sizeof(assets[assetCount].type));
    assets[assetCount].purchaseValue =
        readNonNegative("Enter purchase value (N$): ");
    readRequiredString("Enter department: ", assets[assetCount].department,
                       sizeof(assets[assetCount].department));
    readRequiredString("Enter condition (Good/Fair/Poor): ",
                       assets[assetCount].condition,
                       sizeof(assets[assetCount].condition));

    assetCount++;
    printf("Asset added successfully.\n");
}

void displayAssets(void) {
    if (assetCount == 0) {
        printf("No assets registered.\n");
        return;
    }

    printf("\n%-6s %-22s %-15s %15s %-18s %-12s\n",
           "ID", "Name", "Type", "Value", "Department", "Condition");
    printf("------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < assetCount; i++) {
        printf("%-6d %-22s %-15s %15.2f %-18s %-12s\n",
               assets[i].id,
               assets[i].name,
               assets[i].type,
               assets[i].purchaseValue,
               assets[i].department,
               assets[i].condition);
    }
}

void searchAsset(void) {
    if (assetCount == 0) {
        printf("No assets registered.\n");
        return;
    }

    char search[60];
    readRequiredString("Enter asset name to search: ", search, sizeof(search));

    for (int i = 0; i < assetCount; i++) {
        if (strcmp(assets[i].name, search) == 0) {
            printf("\nAsset found:\n");
            printf("ID: %d\n", assets[i].id);
            printf("Name: %s\n", assets[i].name);
            printf("Type: %s\n", assets[i].type);
            printf("Purchase value: N$%.2f\n", assets[i].purchaseValue);
            printf("Department: %s\n", assets[i].department);
            printf("Condition: %s\n", assets[i].condition);
            return;
        }
    }

    printf("Asset not found. Search is case-sensitive.\n");
}
