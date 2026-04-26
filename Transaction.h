#pragma once

#include <iostream>
#include <string>

using namespace std;



class Transaction
{

protected:

    int id;
    double amount;
    string date;
    string description;
    string categoryName;



public:

    Transaction();

    Transaction(int i, double a, string d, string des, string c);



    void setId(int i);
    void setAmount(double a);
    void setDate(string d);
    void setDescription(string des);
    void setCategoryName(string c);



    int getId();
    double getAmount();
    string getDate();
    string getDescription();
    string getCategoryName();



    virtual void display();

};