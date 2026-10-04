#include <stdio.h>
#include "assets.h"
#include "utils.h"

Asset assets[MAX_ASSETS];
int assetCount = 0;

static int assetIdExists(int id)
{
    for (int i = 0; i < assetCount; i++) if (assets[i].id == id) return 1;
    return 0;
}

void addAsset(void)
{
    if (assetCount >= MAX_ASSETS) { printf("Asset storage is full.\n"); return; }
    int id;
    while (1) {
        id = readInt("Enter asset ID: ", 1, 2147483647);
        if (assetIdExists(id)) printf("That asset ID already exists.\n"); else break;
    }
    assets[assetCount].id = id;
    readString("Enter asset name: ", assets[assetCount].name, sizeof(assets[assetCount].name));
    readString("Enter asset type: ", assets[assetCount].type, sizeof(assets[assetCount].type));
    assets[assetCount].purchaseValue = readDouble("Enter purchase value (N$): ", 0.0);
    readString("Enter department: ", assets[assetCount].department, sizeof(assets[assetCount].department));
    readString("Enter condition (Good/Fair/Poor): ", assets[assetCount].condition, sizeof(assets[assetCount].condition));
    assetCount++;
    printf("Asset added successfully.\n");
}

void displayAssets(void)
{
    if (assetCount == 0) { printf("No assets registered.\n"); return; }
    printf("\n%-6s %-22s %-15s %15s %-18s %-12s\n", "ID", "Name", "Type", "Value", "Department", "Condition");
    printLine('-', 95);
    for (int i = 0; i < assetCount; i++) printf("%-6d %-22s %-15s %15.2f %-18s %-12s\n", assets[i].id, assets[i].name, assets[i].type, assets[i].purchaseValue, assets[i].department, assets[i].condition);
}

void searchAsset(void)
{
    if (assetCount == 0) { printf("No assets registered.\n"); return; }
    char search[60];
    readString("Enter asset name to search: ", search, sizeof(search));
    for (int i = 0; i < assetCount; i++) {
        if (containsIgnoreCase(assets[i].name, search)) {
            printf("\nAsset found:\nID: %d\nName: %s\nType: %s\nPurchase value: N$%.2f\nDepartment: %s\nCondition: %s\n", assets[i].id, assets[i].name, assets[i].type, assets[i].purchaseValue, assets[i].department, assets[i].condition);
            return;
        }
    }
    printf("Asset not found.\n");
}
