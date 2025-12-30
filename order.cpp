#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// ===== CSV PATH =====
#define ORDERS_CSV "C:/Users/PMLS/OneDrive/Desktop/bismillah/orders.csv"
const int MAX_ORDERS = 100;

// ===== STRUCT =====
struct Order {
    string orderID;
    string customerName;
    string itemID;
    string quantity;
};

// ===== GLOBALS =====
Order orders[MAX_ORDERS];
int orderCount = 0;

// ===== LOAD ORDERS FROM CSV =====
void loadOrders() {
    ifstream file(ORDERS_CSV);
    if (!file.is_open()) return;

    string line;
    orderCount = 0;
    while (getline(file, line) && orderCount < MAX_ORDERS) {
        stringstream ss(line);
        getline(ss, orders[orderCount].orderID, ',');
        getline(ss, orders[orderCount].customerName, ',');
        getline(ss, orders[orderCount].itemID, ',');
        getline(ss, orders[orderCount].quantity, ',');
        orderCount++;
    }
    file.close();
}

// ===== SAVE ORDERS TO CSV =====
void saveOrders() {
    ofstream file(ORDERS_CSV);
    for (int i = 0; i < orderCount; i++) {
        file << orders[i].orderID << ","
             << orders[i].customerName << ","
             << orders[i].itemID << ","
             << orders[i].quantity << "\n";
    }
    file.close();
}

// ===== ADD ORDER =====
void addOrder() {
    if (orderCount >= MAX_ORDERS) {
        cout << "Order limit reached!\n";
        return;
    }

    Order o;
    cout << "Order ID: ";
    cin >> o.orderID;
    cin.ignore();
    cout << "Customer Name: ";
    getline(cin, o.customerName);
    cout << "Item ID: ";
    cin >> o.itemID;
    cout << "Quantity: ";
    cin >> o.quantity;

    orders[orderCount++] = o;
    saveOrders();
    cout << "Order successfully added.\n";
}

// ===== DISPLAY ORDERS =====
void displayOrders() {
    loadOrders();
    if (orderCount == 0) {
        cout << "No orders found.\n";
        return;
    }
    cout << "\nOrderID\tCustomer\tItemID\tQty\n";
    cout << "-----------------------------------\n";
    for (int i = 0; i < orderCount; i++) {
        cout << orders[i].orderID << "\t"
             << orders[i].customerName << "\t"
             << orders[i].itemID << "\t"
             << orders[i].quantity << "\n";
    }
}

// ===== UPDATE ORDER =====
void updateOrder() {
    loadOrders();
    string id;
    cout << "Enter Order ID to update: ";
    cin >> id;
    bool found = false;

    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderID == id) {
            cout << "New Item ID: ";
            cin >> orders[i].itemID;
            cout << "New Quantity: ";
            cin >> orders[i].quantity;
            found = true;
            break;
        }
    }

    if (found) {
        saveOrders();
        cout << "Order updated successfully.\n";
    } else {
        cout << "Order ID not found.\n";
    }
}

// ===== DELETE ORDER =====
void deleteOrder() {
    loadOrders();
    string id;
    cout << "Enter Order ID to delete: ";
    cin >> id;
    bool found = false;

    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderID == id) {
            // Shift orders left
            for (int j = i; j < orderCount - 1; j++) {
                orders[j] = orders[j + 1];
            }
            orderCount--;
            found = true;
            break;
        }
    }

    if (found) {
        saveOrders();
        cout << "Order deleted successfully.\n";
    } else {
        cout << "Order ID not found.\n";
    }
}

// ===== MAIN FUNCTION =====
int main() {
    int choice;
    do {
        cout << "\n--- ORDER MANAGEMENT SYSTEM ---\n";
        cout << "1. Add Order\n";
        cout << "2. Display Orders\n";
        cout << "3. Update Order\n";
        cout << "4. Delete Order\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addOrder(); break;
            case 2: displayOrders(); break;
            case 3: updateOrder(); break;
            case 4: deleteOrder(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
