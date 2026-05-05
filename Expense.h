#pragma once

#include "transaction.h"



class Expense : public Transaction
{

private:

    string paymentMethod;



public:

    Expense();

    Expense(int i, double a, string d, string des, string c, string p);



    void setPaymentMethod(string p);

    string getPaymentMethod();



    void display();

};