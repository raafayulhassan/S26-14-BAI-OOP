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
    string transactionType;



public:

    Transaction();

    Transaction(int i, double a, string d, string des, string c, string type);



    virtual ~Transaction();



    void setId(int i);
    void setAmount(double a);
    void setDate(string d);
    void setDescription(string des);
    void setCategoryName(string c);
    void setTransactionType(string type);



    int getId();
    double getAmount();
    string getDate();
    string getDescription();
    string getCategoryName();
    string getTransactionType();

    //void addRecord();
    //void editRecord();
    //void deleteRecord();

    //double operator+(const Transaction& obj) const;
    //bool operator==(const Transaction& obj) const;
    //bool operator>(const Transaction& obj) const;


    virtual void display();

};


   

    