#pragma once
#include <string>
using namespace std;

class Transaction {
public:
    string date;
    string category;
    double amount;
    string type;        // "income" or "expense"
    string description;

    Transaction() = default;
    Transaction(string d, string c, double a, string t, string desc);

    string toCSV() const;
    static Transaction fromCSV(const string& line);
};