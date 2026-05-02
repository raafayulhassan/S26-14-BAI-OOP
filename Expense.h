#pragma once

#include "Transaction.h"
#include <iostream>
#include <string>

using namespace std;

class Expense : public Transaction
{
private:
    string expenseType;
    string paymentMethod;
    string notes;

public:
    Expense();
    Expense(int i, double a, string d, string des, string c,
        string et, string pm, string n);

    void setExpenseType(string et);
    void setPaymentMethod(string pm);
    void setNotes(string n);

    string getExpenseType();
    string getPaymentMethod();
    string getNotes();

    void display();
};