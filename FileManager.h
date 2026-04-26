#pragma once

#include <iostream>
#include <fstream>

#include "Transaction.h"
#include "Budget.h"

using namespace std;



class FileManager
{

public:

    FileManager();



    void saveTransactions(Transaction transactions[], int size);

    void loadTransactions(Transaction transactions[], int& size, int capacity);



    void saveBudgets(Budget budgets[], int size);

    void loadBudgets(Budget budgets[], int& size, int capacity);

};