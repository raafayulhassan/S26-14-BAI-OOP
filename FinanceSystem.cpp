#include "FinanceSystem.h"



FinanceSystem::FinanceSystem()
{
    transactionCapacity = 100;
    budgetCapacity = 100;


    transactionCount = 0;
    budgetCount = 0;


    transactions = new Transaction[transactionCapacity];
    budgets = new Budget[budgetCapacity];
}



FinanceSystem::~FinanceSystem()
{
    delete[] transactions;
    delete[] budgets;
}



void FinanceSystem::addTransaction(Transaction t)
{
    if (transactionCount == transactionCapacity)
    {
        int newCapacity = transactionCapacity * 2;

        Transaction* newArray = new Transaction[newCapacity];


        for (int i = 0; i < transactionCount; i++)
        {
            newArray[i] = transactions[i];
        }


        delete[] transactions;

        transactions = newArray;

        transactionCapacity = newCapacity;
    }


    transactions[transactionCount] = t;

    transactionCount++;
}



void FinanceSystem::addBudget(Budget b)
{
    if (budgetCount == budgetCapacity)
    {
        int newCapacity = budgetCapacity * 2;

        Budget* newArray = new Budget[newCapacity];


        for (int i = 0; i < budgetCount; i++)
        {
            newArray[i] = budgets[i];
        }


        delete[] budgets;

        budgets = newArray;

        budgetCapacity = newCapacity;
    }


    budgets[budgetCount] = b;

    budgetCount++;
}



void FinanceSystem::showAllTransactions()
{
    cout << "All Transactions" << endl;
    cout << "----------------" << endl;


    for (int i = 0; i < transactionCount; i++)
    {
        transactions[i].display();
    }
}



void FinanceSystem::showAllBudgets()
{
    cout << "All Budgets" << endl;
    cout << "-----------" << endl;


    for (int i = 0; i < budgetCount; i++)
    {
        budgets[i].display();
    }
}



void FinanceSystem::searchTransactionByCategory(string categoryName)
{
    searchManager.searchByCategory(transactions, transactionCount, categoryName);
}



void FinanceSystem::searchTransactionByDate(string date)
{
    searchManager.searchByDate(transactions, transactionCount, date);
}



void FinanceSystem::searchTransactionByAmount(double amount)
{
    searchManager.searchByAmount(transactions, transactionCount, amount);
}



void FinanceSystem::generateReport()
{
    Report report;

    report.generateReport(transactions, transactionCount, budgets, budgetCount);
}



void FinanceSystem::saveData()
{
    fileManager.saveTransactions(transactions, transactionCount);

    fileManager.saveBudgets(budgets, budgetCount);
}



void FinanceSystem::loadData()
{
    fileManager.loadTransactions(transactions, transactionCount, transactionCapacity);

    fileManager.loadBudgets(budgets, budgetCount, budgetCapacity);
}