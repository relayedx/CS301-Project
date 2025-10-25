#include "Transaction.h"
#include <sstream>
using namespace std;

Transaction::Transaction(string d, string c, double a, string t, string desc)
    : date(d), category(c), amount(a), type(t), description(desc) {}

string Transaction::toCSV() const {
    return date + "," + category + "," + to_string(amount) + "," + type + "," + description;
}

Transaction Transaction::fromCSV(const string& line) {
    istringstream iss(line);
    string date, category, amountStr, type, description;

    getline(iss, date, ',');
    getline(iss, category, ',');
    getline(iss, amountStr, ',');
    getline(iss, type, ',');
    getline(iss, description);

    double amount = stod(amountStr);
    return Transaction(date, category, amount, type, description);
}