#include "income.h"



Income::Income() : Transaction()
{
    source = "not set";
    transactionType = "Income";
}



Income::Income(int i, double a, string d, string des, string c, string s)
    : Transaction(i, a, d, des, c, "Income")
{
    source = s;
}



void Income::setSource(string s)
{
    source = s;
}



string Income::getSource()
{
    return source;
}

//void Income::addIncome()
//{
//    cout << "\nEnter Income ID: ";
//    cin >> id;
//    cout << "Enter Amount: ";
//    cin >> amount;
//    cin.ignore();
//    cout << "Enter Date: ";
//    getline(cin, date);
//    cout << "Enter Description: ";
//    getline(cin, description);
//    cout << "Enter Category Name: ";
//    getline(cin, categoryName);
//    cout << "Enter Source: ";
//    getline(cin, source);
//
//    cout << "Enter Income Type: ";
//    getline(cin, incomeType);
//}
//
//void Income::updateIncome()
//{
//    cout << "\nUpdate Income Record\n";
//    cout << "Enter New Amount: ";
//    cin >> amount;
//    cin.ignore();
//    cout << "Enter New Date: ";
//    getline(cin, date);
//    cout << "Enter New Description: ";
//    getline(cin, description);
//    cout << "Enter New Category Name: ";
//    getline(cin, categoryName);
//    cout << "Enter New Source: ";
//    getline(cin, source);
//    cout << "Enter New Income Type: ";
//    getline(cin, incomeType);
//}

void Income::display()
{
    cout << "Income Transaction" << endl;
    cout << "------------------" << endl;

    cout << "Transaction ID: " << id << endl;
    cout << "Amount: " << amount << endl;
    cout << "Date: " << date << endl;
    cout << "Description: " << description << endl;
    cout << "Category: " << categoryName << endl;
    cout << "Source: " << source << endl;

    cout << endl;
}



