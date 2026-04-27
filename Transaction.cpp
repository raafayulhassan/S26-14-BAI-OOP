#include<Transaction.h>
/*
    int id;
    double amount;
    string date;
    string description;
    string categoryName;
*/
Transaction::Transaction() {
    id = 0;
    amount = 0;
    date = "";
    description = "";
    categoryName = "";
}
Transaction(int i, double a, string d, string des, string c) {
    this->id = i;
    this->amount = a;
    this->date = d;
    this->description = des;
    this->categoryName = c;
}

