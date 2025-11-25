#include "BudgetManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void BudgetManager::addTransaction(const Transaction& t) {
    transactions.push_back(t);
}

void BudgetManager::listTransactions() const {
    cout << "\n--- Transactions ---\n";
    if (transactions.empty()) {
        cout << "No transactions yet.\n";
        return;
    }

    for (const auto& t : transactions) {
        cout << t.date << " | " << setw(10) << left << t.category
             << " | " << setw(8) << left << t.type
             << " | $" << fixed << setprecision(2) << t.amount
             << " | " << t.description << "\n";
    }
}

const vector<Transaction>& BudgetManager::getTransactions() const {
    return transactions;  // Just give me the data, don't print it
}

double BudgetManager::totalIncome() const {
    double sum = 0;
    for (const auto& t : transactions)
        if (t.type == "income") sum += t.amount;
    return sum;
}

double BudgetManager::totalExpense() const {
    double sum = 0;
    for (const auto& t : transactions)
        if (t.type == "expense") sum += t.amount;
    return sum;
}

double BudgetManager::balance() const {
    return totalIncome() - totalExpense();
}

void BudgetManager::saveToFile(const string& filename) const {
    ofstream file(filename);
    for (const auto& t : transactions)
        file << t.toCSV() << "\n";
}

void BudgetManager::loadFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (!line.empty())
            transactions.push_back(Transaction::fromCSV(line));
    }
}