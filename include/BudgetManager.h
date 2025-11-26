#pragma once
#include "Transaction.h"
#include <vector>
#include <map>
using namespace std;

class BudgetManager {
private:
    vector<Transaction> transactions;
    vector<string> categoryList;

public:
    BudgetManager();

    // Transaction Functions
    void addTransaction(const Transaction& t);
    void deleteTransaction(int index);
    void editTransaction(int index, const Transaction& t);

    // Show Data
    void listTransactions() const;
    const vector<Transaction>& getTransactions() const;

    double totalIncome() const;
    double totalExpense() const;
    double balance() const;

    // Category Functions
    void printCategories() const;
    string getCategoryIndex(int i) const;
    int getCategoryCount() const;
    const vector<string>& getCategoryList() const{return categoryList;}

    // Save / Load
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
