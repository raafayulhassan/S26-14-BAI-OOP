#pragma once

#include <iostream>

#include "Transaction.h"
#include "Budget.h"
#include "Report.h"
#include "SearchManager.h"
#include "FileManager.h"

using namespace std;



class FinanceSystem
{

private:

    Transaction* transactions;
    Budget* budgets;


    int transactionCount;
    int budgetCount;

    int transactionCapacity;
    int budgetCapacity;


    SearchManager searchManager;
    FileManager fileManager;



public:

    FinanceSystem();

    ~FinanceSystem();



    void addTransaction(Transaction t);

    void addBudget(Budget b);



    void showAllTransactions();

    void showAllBudgets();



    void searchTransactionByCategory(string categoryName);

    void searchTransactionByDate(string date);

    void searchTransactionByAmount(double amount);



    void generateReport();



    void saveData();

    void loadData();

};