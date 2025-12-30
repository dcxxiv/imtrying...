#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#define MENU_FILE "C:/Users/PMLS/OneDrive/Desktop/bismillah/menu.txt"
#define ORDER_FILE "C:/Users/PMLS/OneDrive/Desktop/bismillah/orders.txt"

// Allowed Order IDs
int allowedIDs[] = {1111,1112,1113,1114,1115,1116,1117,1118,1119,1200};
const int allowedCount = 10;

// ---------- CHECK VALID ORDER ID ----------
bool isValidOrderID(const string &id) {
    for (int i = 0; i < allowedCount; i++)
        if (id == to_string(allowedIDs[i]))
            return true;
    return false;
}

// ---------- GET PRICE FROM MENU ----------
int getPrice(int itemID) {
    ifstream file(MENU_FILE);
    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, price;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, price, ',');

        if (stoi(id) == itemID) {
            file.close();
            return stoi(price);
        }
    }
    file.close();
    return -1;
}

// ---------- ADD ORDER ----------
void addOrder() {
    cout << "\nWhat would you like to eat?\n";

    string orderID, customer;
    int itemID, qty;

    cout << "Enter Order ID: ";
    cin >> orderID;

    if (!isValidOrderID(orderID)) {
        cout << "Invalid Order ID!\n";
        return;
    }

    cin.ignore();
    cout << "Enter Customer Name: ";
    getline(cin, customer);

    cout << "Enter Item ID: ";
    cin >> itemID;

    int price = getPrice(itemID);
    if (price == -1) {
        cout << "Invalid Item ID!\n";
        return;
    }

    cout << "Enter Quantity: ";
    cin >> qty;

    ofstream file(ORDER_FILE, ios::app);
    file << orderID << "," << customer << ","
         << itemID << "," << qty << "," << price << endl;
    file.close();

    cout << "\n------ BILL ------\n";
    cout << "Price: " << price << endl;
    cout << "Quantity: " << qty << endl;
    cout << "Total Bill: " << price * qty << endl;
    cout << "------------------\n";
    cout << "Thanks for your order!\n";
}

// ---------- SHOW ORDERS ----------
void showOrders() {
    ifstream file(ORDER_FILE);
    string line;
    double grandTotal = 0;

    cout << "\nOrderID\tCustomer\tItem\tQty\tPrice\tTotal\n";
    cout << "------------------------------------------------\n";

    getline(file, line); // skip header

    while (getline(file, line)) {
        if (
