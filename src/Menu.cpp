#include "Menu.h"
#include <iostream>
using namespace std;

void Menu::showMenu() {
    cout << "\n=== Simple Budget Tracker ===\n";
    cout << "1. Add Transaction\n";
    cout << "2. View All Transactions\n";
    cout << "3. View Summary\n";
    cout << "0. Save and Exit\n";
    cout << "Choice: ";
}

void Menu::addTransaction() {
    string date, category, type, description;
    double amount;

    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;
    cout << "Enter category: ";
    cin >> category;
    cout << "Enter amount: ";
    cin >> amount;
    cout << "Type (income/expense): ";
    cin >> type;
    cout << "Description: ";
    cin.ignore();
    getline(cin, description);

    Transaction t(date, category, amount, type, description);
    manager.addTransaction(t);
    cout << "Transaction added!\n";
}

void Menu::showSummary() const {
    cout << "\n--- Summary ---\n";
    cout << "Total Income:  $" << manager.totalIncome() << "\n";
    cout << "Total Expense: $" << manager.totalExpense() << "\n";
    cout << "Balance:       $" << manager.balance() << "\n";
}

void Menu::run() {
    manager.loadFromFile(dataFile);

    bool running = true;
    while (running) {
        showMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: addTransaction(); break;
            case 2: manager.listTransactions(); break;
            case 3: showSummary(); break;
            case 0:
                manager.saveToFile(dataFile);
                cout << "Data saved. Goodbye!\n";
                running = false;
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }
}