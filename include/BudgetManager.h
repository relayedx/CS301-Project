#pragma once
#include "Transaction.h"
#include <vector>
using namespace std;

class BudgetManager {
private:
    vector<Transaction> transactions;

public:
    void addTransaction(const Transaction& t);
    void listTransactions() const;
    double totalIncome() const;
    double totalExpense() const;
    double balance() const;

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
};