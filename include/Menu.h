#pragma once
#include "BudgetManager.h"
#include <string>
using namespace std;

class Menu {
private:
    BudgetManager manager;
    string dataFile = "data/transactions.csv";

public:
    void run();
private:
    void showMenu();
    void addTransaction();
    void showSummary() const;
};