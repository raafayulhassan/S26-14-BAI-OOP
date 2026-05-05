#include "Transaction.h"



Transaction::Transaction()
{
    id = 0;
    amount = 0;
    date = "not set";
    description = "not set";
    categoryName = "not set";
    transactionType = "Transaction";
}



Transaction::Transaction(int i, double a, string d, string des, string c, string type)
{
    id = i;
    amount = a;
    date = d;
    description = des;
    categoryName = c;
    transactionType = type;
}



Transaction::~Transaction()
{

}



void Transaction::setId(int i)
{
    id = i;
}



void Transaction::setAmount(double a)
{
    amount = a;
}



void Transaction::setDate(string d)
{
    date = d;
}



void Transaction::setDescription(string des)
{
    description = des;
}



void Transaction::setCategoryName(string c)
{
    categoryName = c;
}



void Transaction::setTransactionType(string type)
{
    transactionType = type;
}



int Transaction::getId()
{
    return id;
}



double Transaction::getAmount()
{
    return amount;
}



string Transaction::getDate()
{
    return date;
}



string Transaction::getDescription()
{
    return description;
}



string Transaction::getCategoryName()
{
    return categoryName;
}



string Transaction::getTransactionType()
{
    return transactionType;
}



void Transaction::display()
{
    cout << "Transaction ID: " << id << endl;
    cout << "Type: " << transactionType << endl;
    cout << "Amount: " << amount << endl;
    cout << "Date: " << date << endl;
    cout << "Description: " << description << endl;
    cout << "Category: " << categoryName << endl;

    cout << endl;
}
//void Transaction::addRecord() {
//    cout << "\nEnter transaction details:\n";
//    cout << "Enter ID: ";
//    cin >> id;
//    cout << "\nEnter amount (PKR): "<<endl;
//    cin >> amount;
//    if (amount < 0) {
//        cout << "Invalid amount! Resetting to zero.";
//        anount = 0;
//    }
//    cout << "\nEnter date in DD/MM/YY: "<<;
//    cin >> date;
//    cin.ignore();
//    cout << "\nEnter description: ";
//    getline(cin, description);
//    cout << "\nEnter category (Food, Bills, Transport, etc): ";
//    cin >> categoryName;
//    cout << "\nRecord added successfully!\n";
//}




//void Transaction:: editRecord() {
//    cout << "Which field do you want to edit?(Enter integer value only) " << endl;
//    cout << "1. Amount" << "\n2. Date" << "\n3. Description" << "\n4. Category";
//    int f;
//    cin >> f;
//    if (f == 1) {
//        cin >> amount;
//    }
//    else if (f == 2) {
//        cin >> date;
//    }
//    else if (f == 3) {
//        cin >> description;
//    }
//    else if (f == 4) {
//        cin >> categoryName;
//    }
//    else {
//        cout << "Invalid input!!Please try again!" << endl;
//        editRecord();
//    }
//
//}




//void Transaction:: deleteRecord() {
//    cout << "Are you sure you want to delete the record? Once deleted, you cannot restore! " << endl;
//    cout << "Enter 1 if YES, 0 if NO" << endl;
//    int c;
//    cin >> c;
//    if (c == 1) {
//        id = 0;
//        amount = 0;
//        date = "";
//        description = "";
//        categoryName = "";
//    }
//    else if (c == 0) {
//        return;
//    }
//    else {
//        cout << "Invalid input!! Please enter a valid option." << endl;
//        return;
//    }
//}

//double Transaction::operator+(const Transaction& obj) const {
//    double total = 0;
//    total = this->amount + obj.amount;
//    return total;
//}
//
//bool Transaction::operator==(const Transaction& obj) const {
//    if (this->id == obj.id) {
//        return true;
//    }
//    else {
//        return false;
//    }
//}
//
//bool Transaction::operator>(const Transaction& obj) const {
//    if (this->amount > obj.amount) {
//        return true;
//    }
//    else {
//        return false;
//    }
//}








