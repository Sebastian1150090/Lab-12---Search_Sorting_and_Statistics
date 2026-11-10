/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: [Sebastian A. Feliciano]
 * Lab: 12 - Search, Sorting and Statistics
 * Description: [It is a C++ console program that stores four maintenance orders and lets the user find one by ID or list all orders in a given area.]
 * Due Date: [11/9/26]
 */

 #include <iostream> // Provides console input and output
#include <iomanip> // Provides decimal formatting
#include <string> // Provides string and getline
using namespace std;

struct MaintenanceOrder {
    int id = 0;
    string area;
    double estimatedHours = 0.0;
};

int findOrderById(const MaintenanceOrder orders[], int count, int targetId);
int displayOrdersByArea(const MaintenanceOrder orders[], int count, string targetArea);

int main() {
    const int ORDER_COUNT = 4;
    MaintenanceOrder orders[ORDER_COUNT] = {};
    int targetId = 0;
    string targetArea;

    for (int index = 0; index < ORDER_COUNT; index++) {
        cout << "Enter ID for order " << index + 1 << ": ";
        cin >> orders[index].id;
        cout << "Enter area for order " << index + 1 << ": ";
        getline(cin >> ws, orders[index].area);
        cout << "Enter estimated hours: ";
        cin >> orders[index].estimatedHours;
    }

    cout << "Enter an order ID to find: ";
    cin >> targetId;
    int foundIndex = findOrderById(orders, ORDER_COUNT, targetId);
    if (foundIndex == -1) {
        cout << "Order not found." << endl;
    } else {
        cout << fixed << setprecision(2);
        cout << "Found order " << orders[foundIndex].id
             << " in " << orders[foundIndex].area
             << " with " << orders[foundIndex].estimatedHours << " hours." << endl;
    }

    cout << "Enter an area to list its orders: ";
    getline(cin >> ws, targetArea);
    int matchCount = displayOrdersByArea(orders, ORDER_COUNT, targetArea);
    cout << "Orders in area: " << matchCount << endl;
    return 0;
}

int findOrderById(const MaintenanceOrder orders[], int count, int targetId) {
    for (int index = 0; index < count; index++) {
        if (orders[index].id == targetId) {
            return index; // Stops because an ID identifies one order
        }
    }
    return -1; // Reports that no valid index was found
}

int displayOrdersByArea(const MaintenanceOrder orders[], int count, string targetArea) {
    int matchCount = 0;
    cout << fixed << setprecision(2);
    for (int index = 0; index < count; index++) {
        if (orders[index].area == targetArea) {
            cout << "ID: " << orders[index].id
                 << " | Hours: " << orders[index].estimatedHours << endl;
            matchCount++; // Counts every matching order
        }
    }
    return matchCount;
}