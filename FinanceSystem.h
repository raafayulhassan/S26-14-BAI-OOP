#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "transaction.h"
#include "budget.h"
#include "report.h"
#include "alert.h"
#include "searchmanager.h"
#include "filemanager.h"

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


    double monthlySalary;
    double monthlySpendingLimit;
    string activeMonth;


    SearchManager searchManager;
    FileManager fileManager;


    string getMonthPrefix(string month);
    void resetBudgetUsage();
    void rebuildBudgetUsageFromTransactions();


public:

    FinanceSystem();

    ~FinanceSystem();



    void clearData();

    void clearMonthDataOnly();

    void resetEverything();



    void setMonthlySalary(double salary);

    void setMonthlySpendingLimit(double limit);

    void setActiveMonth(string month);



    double getMonthlySalary();

    double getMonthlySpendingLimit();

    string getActiveMonth();



    void addTransaction(Transaction t);

    void addBudget(Budget b);

    bool addBudgetOnce(Budget b);

    bool budgetCategoryExists(string categoryName);

    bool canAddBudgetLimit(double limitAmount);

    void addExpenseForBudget(string categoryName, double amount, string month);



    void showAllTransactions();

    void showAllBudgets();



    void searchTransactionByCategory(string categoryName);

    void searchTransactionByDate(string date);

    void searchTransactionByAmount(double amount);



    void generateReport();

    void checkAllBudgetAlerts();



    void saveData();

    void loadData();



    void saveGlobalBudgetDomains();

    bool loadGlobalBudgetDomains();

    void saveMonthData(string month);

    bool loadMonthData(string month);

    void saveReportForMonth(string month);

    bool hasAnyData();



    int getTransactionCount();

    int getBudgetCount();

    int getNextTransactionId();

    int getNextBudgetId();

    Transaction* getTransactionAt(int index);

    Budget* getBudgetAt(int index);



    double getTotalIncome();

    double getTotalExpense();

    double getBalance();

    double getTotalBudgetLimit();

    double getTotalBudgetUsed();

    double getRemainingSpendLimit();

};
