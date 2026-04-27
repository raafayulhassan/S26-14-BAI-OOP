#pragma once

#include "Transaction.h"



class Expense : public Transaction
{

private:

    string paymentMethod;
    string expenseType;
    string  Notes;


public:

    Expense();

    Expense(int i, double a, string d, string des, string c, string p,string e,string n);



    void setPaymentMethod(string p);

    string getPaymentMethod();



    void display();

};