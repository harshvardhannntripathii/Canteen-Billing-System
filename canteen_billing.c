#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEMS 20
#define MAX_ORDERS 50
#define ID_LEN 10
#define NAME_LEN 50

#define BORDER "==========================================\n"
#define MENU_FMT "%-5s | %-20s | Rs.%-6.2f | %-8d\n"
#define STOCK_FMT "%-5s | %-20s | Rs.%-6.2f | %-8d | %s\n"
#define BILL_FMT "%-20s | %3d | Rs.%-7.2f | Rs.%-7.2f\n"

typedef struct {
    char id[ID_LEN];
    char name[NAME_LEN];
    float price;
    int quantity;
} FoodItem;

typedef struct {
    FoodItem item;
    int menuIndex;
    int orderedQuantity;
    float subtotal;
} OrderItem;

FoodItem menu[MAX_ITEMS];
OrderItem orders[MAX_ORDERS];
int menuCount = 0;
int orderCount = 0;

void initMenu();
void printBorder();
void printHeader(const char* title, const char* fmt, const char* c1, const char* c2, const char* c3, const char* c4);
void printMenuTable(int showStockOnly);
int findItem(const char* id);
void searchItem();
void placeOrder();
void generateBill();
void viewStock();
void clearBuf();
int getInt(int min, int max, const char* prompt);

int main() {
    int choice;
    initMenu();

    printf("\n%s   SMART CANTEEN BILLING SYSTEM\n%s", BORDER, BORDER);

    do {
        printf("\n%s   MAIN MENU\n%s", BORDER, BORDER);
        printf("1. Display Food Menu\n");
        printf("2. Search Food Item\n");
        printf("3. Place Order\n");
        printf("4. Generate Bill\n");
        printf("5. View Available Stock\n");
        printf("6. Exit\n");
        printf("%sEnter your choice: ", BORDER);

        choice = getInt(1, 6, "");

        switch (choice) {
            case 1: printMenuTable(0); break;
            case 2: searchItem(); break;
            case 3: placeOrder(); break;
            case 4: generateBill(); break;
            case 5: viewStock(); break;
            case 6:
                printf("\nThank you for using Smart Canteen Billing System!\n");
                printf("Have a great day!\n\n");
                break;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}

void initMenu() {
    FoodItem items[] = {
        {"101", "Burger", 50.0f, 20},
        {"102", "Pizza", 100.0f, 15},
        {"103", "Sandwich", 40.0f, 25},
        {"104", "Samosa", 15.0f, 30},
        {"105", "Cold Coffee", 60.0f, 20},
        {"106", "Tea", 10.0f, 50},
        {"107", "French Fries", 45.0f, 20},
        {"108", "Noodles", 70.0f, 15},
        {"109", "Dosa", 50.0f, 20},
        {"110", "Juice", 30.0f, 25},
        {"111", "Chocolate Cake", 80.0f, 10},
        {"112", "Veg Roll", 35.0f, 25}
    };
    memcpy(menu, items, sizeof(items));
    menuCount = 12;
}

void printBorder() { printf("%s", BORDER); }

void printHeader(const char* title, const char* fmt, const char* c1, const char* c2, const char* c3, const char* c4) {
    printBorder();
    printf("      %s\n", title);
    printBorder();
    printf(fmt, c1, c2, c3, c4);
    printf("--------------------------------------------\n");
}

void printMenuTable(int showStockOnly) {
    printHeader("FOOD MENU", MENU_FMT, "ID", "Food Item", "Price", "Quantity");
    for (int i = 0; i < menuCount; i++)
        if (!showStockOnly || menu[i].quantity > 0)
            printf(MENU_FMT, menu[i].id, menu[i].name, menu[i].price, menu[i].quantity);
    printBorder();
}

int findItem(const char* id) {
    for (int i = 0; i < menuCount; i++)
        if (strcmp(menu[i].id, id) == 0) return i;
    return -1;
}

void searchItem() {
    char id[ID_LEN];
    printf("\n%s       SEARCH FOOD ITEM\n%s", BORDER, BORDER);
    printf("Enter Food ID to search: ");
    scanf("%s", id);
    clearBuf();

    int idx = findItem(id);
    if (idx != -1) {
        printf("\n--- Food Item Found ---\n");
        printf("Food ID    : %s\n", menu[idx].id);
        printf("Food Name  : %s\n", menu[idx].name);
        printf("Price      : Rs.%.2f\n", menu[idx].price);
        printf("Available  : %d\n", menu[idx].quantity);
        printf("Status     : %s\n", menu[idx].quantity > 0 ? "Available" : "Out of Stock");
    } else {
        printf("\nError: Food item with ID '%s' not found!\n", id);
    }
    printBorder();
}

void placeOrder() {
    char id[ID_LEN];
    int qty, idx;

    if (orderCount >= MAX_ORDERS) {
        printf("\nError: Maximum order limit reached!\n");
        return;
    }

    printf("\n%s         PLACE ORDER\n%s", BORDER, BORDER);
    printMenuTable(1);

    do {
        if (orderCount >= MAX_ORDERS) {
            printf("\nMaximum order limit reached!\n");
            break;
        }

        printf("\nEnter Food ID (or '0' to finish): ");
        scanf("%s", id);
        clearBuf();

        if (strcmp(id, "0") == 0) break;

        idx = findItem(id);
        if (idx == -1) {
            printf("Error: Invalid Food ID '%s'! Please try again.\n", id);
            continue;
        }
        if (menu[idx].quantity <= 0) {
            printf("Error: '%s' is out of stock!\n", menu[idx].name);
            continue;
        }

        qty = getInt(1, menu[idx].quantity, "Enter Quantity: ");
        if (qty > menu[idx].quantity) {
            printf("Error: Insufficient stock! Only %d available.\n", menu[idx].quantity);
            continue;
        }

        int existing = -1;
        for (int i = 0; i < orderCount; i++)
            if (orders[i].menuIndex == idx) { existing = i; break; }

        if (existing != -1) {
            if (orders[existing].orderedQuantity + qty > menu[idx].quantity) {
                printf("Error: Total ordered quantity would exceed available stock!\n");
                continue;
            }
            orders[existing].orderedQuantity += qty;
            orders[existing].subtotal = orders[existing].orderedQuantity * orders[existing].item.price;
            printf("Updated %s quantity to %d\n", menu[idx].name, orders[existing].orderedQuantity);
        } else {
            orders[orderCount] = (OrderItem){menu[idx], idx, qty, qty * menu[idx].price};
            orderCount++;
            printf("Added %s x %d to order\n", menu[idx].name, qty);
        }

        printf("\nAdd another item? (y/n): ");
        char c; scanf(" %c", &c); clearBuf();
        if (c != 'y' && c != 'Y') break;
    } while (1);

    if (orderCount > 0)
        printf("\nOrder placed successfully! Generate bill to confirm.\n");
    else
        printf("\nNo items ordered.\n");
    printBorder();
}

void generateBill() {
    float total = 0;

    printf("\n%s         BILL RECEIPT\n%s", BORDER, BORDER);

    if (orderCount == 0) {
        printf("\nNo items in order! Please place an order first.\n");
        printBorder();
        return;
    }

    printf("\n%-20s | %-3s | %-10s | %-10s\n", "Item", "Qty", "Unit Price", "Subtotal");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < orderCount; i++) {
        printf(BILL_FMT, orders[i].item.name, orders[i].orderedQuantity, orders[i].item.price, orders[i].subtotal);
        total += orders[i].subtotal;
    }

    printf("------------------------------------------------------\n");
    printf("%-37s Rs.%.2f\n", "Grand Total:", total);
    printBorder();

    printf("\nConfirm order? (y/n): ");
    char c; scanf(" %c", &c); clearBuf();

    if (c == 'y' || c == 'Y') {
        for (int i = 0; i < orderCount; i++)
            menu[orders[i].menuIndex].quantity -= orders[i].orderedQuantity;

        printf("\nOrder Confirmed! Stock updated.\n");
        printBorder();
        printf("\nUpdated Stock:\n");
        for (int i = 0; i < orderCount; i++)
            printf("%s: %d\n", menu[orders[i].menuIndex].name, menu[orders[i].menuIndex].quantity);

        orderCount = 0;
    } else {
        printf("\nOrder cancelled. Items remain in cart.\n");
        printBorder();
    }
}

void viewStock() {
    printHeader("AVAILABLE STOCK INVENTORY", STOCK_FMT, "ID", "Food Item", "Price", "Qty");
    for (int i = 0; i < menuCount; i++)
        printf(STOCK_FMT, menu[i].id, menu[i].name, menu[i].price, menu[i].quantity,
               menu[i].quantity > 0 ? "In Stock" : "Out of Stock");
    printBorder();
}

void clearBuf() {
    int c; while ((c = getchar()) != '\n' && c != EOF);
}

int getInt(int min, int max, const char* prompt) {
    int val, r;
    while (1) {
        if (*prompt) printf("%s", prompt);
        r = scanf("%d", &val);
        clearBuf();
        if (r != 1 || val < min || val > max) {
            printf("Invalid input! Please enter a number between %d and %d: ", min, max);
            continue;
        }
        return val;
    }
}