#include "Expense.h"
Expense::Expense() : Transaction()
{
    expenseType = "";
    paymentMethod = "";
    notes = "";
}

Expense::Expense(int i, double a, string d, string des, string c,
    string et, string pm, string n)
    : Transaction(i, a, d, des, c)
{
    expenseType = et;
    paymentMethod = pm;
    notes = n;
}

void Expense::setExpenseType(string et)
{
    expenseType = et;
}

void Expense::setPaymentMethod(string pm)
{
    paymentMethod = pm;
}

void Expense::setNotes(string n)
{
    notes = n;
}

string Expense::getExpenseType()
{
    return expenseType;
}

string Expense::getPaymentMethod()
{
    return paymentMethod;
}

string Expense::getNotes()
{
    return notes;
}

void Expense::display()
{
    Transaction::display();

    cout << "Expense Type: " << expenseType << endl;
    cout << "Payment Method: " << paymentMethod << endl;
    cout << "Notes: " << notes << endl;
}