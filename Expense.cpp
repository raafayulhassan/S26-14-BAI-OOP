#include "expense.h"



Expense::Expense() : Transaction()
{
    paymentMethod = "not set";
    transactionType = "Expense";
}



Expense::Expense(int i, double a, string d, string des, string c, string p)
    : Transaction(i, a, d, des, c, "Expense")
{
    paymentMethod = p;
}



void Expense::setPaymentMethod(string p)
{
    paymentMethod = p;
}



string Expense::getPaymentMethod()
{
    return paymentMethod;
}



void Expense::display()
{
    cout << "Expense Transaction" << endl;
    cout << "-------------------" << endl;

    cout << "Transaction ID: " << id << endl;
    cout << "Amount: " << amount << endl;
    cout << "Date: " << date << endl;
    cout << "Description: " << description << endl;
    cout << "Category: " << categoryName << endl;
    cout << "Payment Method: " << paymentMethod << endl;

    cout << endl;
}
