#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "transaction.h"
#include "budget.h"

using namespace std;



class FileManager
{

public:

    FileManager();



    void saveTransactions(Transaction transactions[], int size);

    void loadTransactions(Transaction transactions[], int& size, int capacity);



    void saveBudgets(Budget budgets[], int size);

    void loadBudgets(Budget budgets[], int& size, int capacity);



    void saveTransactionsToFile(Transaction transactions[], int size, string fileName);

    bool loadTransactionsFromFile(Transaction transactions[], int& size, int capacity, string fileName);



    void saveBudgetsToFile(Budget budgets[], int size, string fileName);

    bool loadBudgetsFromFile(Budget budgets[], int& size, int capacity, string fileName);



    void saveBudgetDomainsToFile(Budget budgets[], int size, string fileName);

    bool loadBudgetDomainsFromFile(Budget budgets[], int& size, int capacity, string fileName);



    void saveMonthInfo(string fileName, string month, double salary, double spendingLimit);

    bool loadMonthInfo(string fileName, string& month, double& salary, double& spendingLimit);

};
