#include"Transaction.h"
#include"Category.h"
using namespace std;
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
Transaction::Transaction(int i, double a, string d, string des, string c) {
    this->id = i;
    this->amount = a;
    this->date = d;
    this->description = des;
    this->categoryName = c;
}




void Transaction::setId(int i) {
    this->id = i;
}
void Transaction::void setAmount(double a) {
    this->amount = a;
}
void Transaction::void setDate(string d) {
    this->date = d;
}
void Transaction::void setDescription(string des) {
    this->description = des;
}
void Transaction::void setCategoryName(string c) {
    this->categoryName = c;
}




int Transaction:: getId() {
    return id;
}
int Transaction:: getAmount() {
    return amount;
}
string Transaction::getDate() {
    return date;
}
string Transaction::getDescription() {
    return description
}
string Transaction:: getCategoryName() {
    return categoryName;
}




void Transaction::addRecord() {
    cout << "\nEnter transaction details:\n";
    cout << "Enter ID: ";
    cin >> id;
    cout << "\nEnter amount (PKR): "<<endl;
    cin >> amount;
    if (amount < 0) {
        cout << "Invalid amount! Resetting to zero.";
        anount = 0;
    }
    cout << "\nEnter date in DD/MM/YY: "<<;
    cin >> date;
    cin.ignore();
    cout << "\nEnter description: ";
    getline(cin, description);
    cout << "\nEnter category (Food, Bills, Transport, etc): ";
    cin >> categoryName;
    cout << "\nRecord added successfully!\n";
}




void Transaction:: editRecord() {
    cout << "Which field do you want to edit?(Enter integer value only) " << endl;
    cout << "1. Amount" << "\n2. Date" << "\n3. Description" << "\n4. Category";
    int f;
    cin >> f;
    if (f == 1) {
        cin >> amount;
    }
    else if (f == 2) {
        cin >> date;
    }
    else if (f == 3) {
        cin >> description;
    }
    else if (f == 4) {
        cin >> categoryName;
    }
    else {
        cout << "Invalid input!!Please try again!" << endl;
        editRecord();
    }

}




void Transaction:: deleteRecord() {
    cout << "Are you sure you want to delete the record? Once deleted, you cannot restore! " << endl;
    cout << "Enter 1 if YES, 0 if NO" << endl;
    int c;
    cin >> c;
    if (c == 1) {
        id = 0;
        amount = 0;
        date = "";
        description = "";
        categoryName = "";
    }
    else if (c == 0) {
        return;
    }
    else {
        cout << "Invalid input!! Please enter a valid option." << endl;
        return;
    }
}




void Transaction::display() {
    cout << "ID: " << id << endl;
    cout << "Amount: " << amount<<endl;
    cout << "Date: " << date<<endl;
    cout << "Description: " << description << endl;
    cout << "Category: " << categoryName<<endl;
}
