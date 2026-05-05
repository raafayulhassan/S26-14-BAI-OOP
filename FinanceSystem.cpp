#include "financesystem.h"

#include <cstdio>



FinanceSystem::FinanceSystem()
{
    transactionCapacity = 100;
    budgetCapacity = 100;


    transactionCount = 0;
    budgetCount = 0;


    monthlySalary = 0;
    monthlySpendingLimit = 0;
    activeMonth = "January";


    transactions = new Transaction[transactionCapacity];
    budgets = new Budget[budgetCapacity];

    loadGlobalBudgetDomains();
}



FinanceSystem::~FinanceSystem()
{
    delete[] transactions;
    delete[] budgets;
}



string FinanceSystem::getMonthPrefix(string month)
{
    string result = "";

    for (int i = 0; i < static_cast<int>(month.length()); i++)
    {
        char ch = month[i];

        if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch + 32;
        }

        if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
        {
            result = result + ch;
        }
    }

    if (result == "")
    {
        result = "month";
    }

    return result;
}



void FinanceSystem::resetBudgetUsage()
{
    for (int i = 0; i < budgetCount; i++)
    {
        budgets[i].setUsedAmount(0);
    }
}



void FinanceSystem::rebuildBudgetUsageFromTransactions()
{
    resetBudgetUsage();

    for (int i = 0; i < transactionCount; i++)
    {
        if (transactions[i].getTransactionType() == "Expense")
        {
            for (int j = 0; j < budgetCount; j++)
            {
                if (budgets[j].getCategoryName() == transactions[i].getCategoryName())
                {
                    budgets[j].addUsedAmount(transactions[i].getAmount());
                }
            }
        }
    }
}



void FinanceSystem::clearData()
{
    transactionCount = 0;
    budgetCount = 0;
    monthlySalary = 0;
    monthlySpendingLimit = 0;
}



void FinanceSystem::clearMonthDataOnly()
{
    transactionCount = 0;
    monthlySalary = 0;
    monthlySpendingLimit = 0;

    resetBudgetUsage();
}





void FinanceSystem::resetEverything()
{
    transactionCount = 0;
    budgetCount = 0;
    monthlySalary = 0;
    monthlySpendingLimit = 0;
    activeMonth = "January";


    remove("transactions.txt");
    remove("budgets.txt");
    remove("budget_domains.txt");


    string monthNames[12] =
    {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };


    for (int i = 0; i < 12; i++)
    {
        string prefix = getMonthPrefix(monthNames[i]);

        remove((prefix + "_month_info.txt").c_str());
        remove((prefix + "_transactions.txt").c_str());
        remove((prefix + "_report.txt").c_str());
    }
}


void FinanceSystem::setMonthlySalary(double salary)
{
    monthlySalary = salary;
}



void FinanceSystem::setMonthlySpendingLimit(double limit)
{
    monthlySpendingLimit = limit;
}



void FinanceSystem::setActiveMonth(string month)
{
    activeMonth = month;
}



double FinanceSystem::getMonthlySalary()
{
    return monthlySalary;
}



double FinanceSystem::getMonthlySpendingLimit()
{
    return monthlySpendingLimit;
}



string FinanceSystem::getActiveMonth()
{
    return activeMonth;
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


    if (t.getTransactionType() == "Expense")
    {
        for (int i = 0; i < budgetCount; i++)
        {
            if (budgets[i].getCategoryName() == t.getCategoryName())
            {
                budgets[i].addUsedAmount(t.getAmount());
            }
        }
    }
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


    b.setUsedAmount(0);

    budgets[budgetCount] = b;

    budgetCount++;
}



bool FinanceSystem::addBudgetOnce(Budget b)
{
    if (budgetCategoryExists(b.getCategoryName()) == true)
    {
        return false;
    }

    addBudget(b);
    saveGlobalBudgetDomains();

    return true;
}



bool FinanceSystem::budgetCategoryExists(string categoryName)
{
    for (int i = 0; i < budgetCount; i++)
    {
        if (budgets[i].getCategoryName() == categoryName)
        {
            return true;
        }
    }

    return false;
}



bool FinanceSystem::canAddBudgetLimit(double limitAmount)
{
    if (monthlySpendingLimit <= 0)
    {
        return true;
    }

    if (getTotalBudgetLimit() + limitAmount <= monthlySpendingLimit)
    {
        return true;
    }

    return false;
}



void FinanceSystem::addExpenseForBudget(string categoryName, double amount, string month)
{
    Transaction expense(getNextTransactionId(), amount, month, "Actual spending", categoryName, "Expense");

    addTransaction(expense);
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
    cout << "Global Budget Domains" << endl;
    cout << "---------------------" << endl;


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



void FinanceSystem::checkAllBudgetAlerts()
{
    Alert alert;


    cout << "Budget Alerts" << endl;
    cout << "-------------" << endl;


    for (int i = 0; i < budgetCount; i++)
    {
        alert.checkBudget(budgets[i]);
        alert.showAlert();
    }


    cout << endl;
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

    rebuildBudgetUsageFromTransactions();
}



void FinanceSystem::saveGlobalBudgetDomains()
{
    fileManager.saveBudgetDomainsToFile(budgets, budgetCount, "budget_domains.txt");
}



bool FinanceSystem::loadGlobalBudgetDomains()
{
    bool loaded = fileManager.loadBudgetDomainsFromFile(budgets, budgetCount, budgetCapacity, "budget_domains.txt");

    resetBudgetUsage();

    return loaded;
}



void FinanceSystem::saveMonthData(string month)
{
    activeMonth = month;

    string prefix = getMonthPrefix(month);

    saveGlobalBudgetDomains();

    fileManager.saveMonthInfo(prefix + "_month_info.txt", month, monthlySalary, monthlySpendingLimit);
    fileManager.saveTransactionsToFile(transactions, transactionCount, prefix + "_transactions.txt");

    saveReportForMonth(month);
}



bool FinanceSystem::loadMonthData(string month)
{
    clearMonthDataOnly();

    activeMonth = month;

    loadGlobalBudgetDomains();

    string prefix = getMonthPrefix(month);
    string loadedMonth = month;

    bool foundInfo = fileManager.loadMonthInfo(prefix + "_month_info.txt", loadedMonth, monthlySalary, monthlySpendingLimit);

    bool foundTransactions = fileManager.loadTransactionsFromFile(transactions, transactionCount, transactionCapacity, prefix + "_transactions.txt");

    rebuildBudgetUsageFromTransactions();

    activeMonth = month;

    if (foundInfo == true || foundTransactions == true)
    {
        return true;
    }

    return false;
}



void FinanceSystem::saveReportForMonth(string month)
{
    string prefix = getMonthPrefix(month);

    ofstream file;

    file.open(prefix + "_report.txt");


    double totalSpend = getTotalBudgetUsed();
    double savings = monthlySalary - totalSpend;


    file << "Budget & Expense Architect Report" << endl;
    file << "Month: " << month << endl;
    file << endl;

    file << "Monthly Salary: Rs. " << fixed << setprecision(0) << monthlySalary << endl;
    file << "Total Spending Limit: Rs. " << fixed << setprecision(0) << monthlySpendingLimit << endl;
    file << "Global Budget Domains: Rs. " << fixed << setprecision(0) << getTotalBudgetLimit() << endl;
    file << "Actual Spend: Rs. " << fixed << setprecision(0) << totalSpend << endl;
    file << "Savings: Rs. " << fixed << setprecision(0) << savings << endl;
    file << endl;

    file << "Category | Limit | Actual | Variance | % of Total Spend" << endl;
    file << "---------------------------------------------------------" << endl;

    for (int i = 0; i < budgetCount; i++)
    {
        double limit = budgets[i].getLimitAmount();
        double actual = budgets[i].getUsedAmount();
        double variance = limit - actual;
        double percent = 0;

        if (totalSpend > 0)
        {
            percent = (actual / totalSpend) * 100;
        }

        file << budgets[i].getCategoryName() << " | ";
        file << "Rs. " << fixed << setprecision(0) << limit << " | ";
        file << "Rs. " << fixed << setprecision(0) << actual << " | ";

        if (variance < 0)
        {
            file << "Over Rs. " << fixed << setprecision(0) << -variance << " | ";
        }
        else
        {
            file << "Under Rs. " << fixed << setprecision(0) << variance << " | ";
        }

        file << fixed << setprecision(1) << percent << "%" << endl;
    }

    file << endl;
    file << "Expense Circle" << endl;
    file << "--------------" << endl;

    for (int i = 0; i < budgetCount; i++)
    {
        double percent = 0;

        if (totalSpend > 0)
        {
            percent = (budgets[i].getUsedAmount() / totalSpend) * 100;
        }

        int blocks = static_cast<int>(percent / 5);

        file << budgets[i].getCategoryName() << " ";

        for (int j = 0; j < blocks; j++)
        {
            file << "#";
        }

        file << " " << fixed << setprecision(1) << percent << "%" << endl;
    }

    file.close();
}



bool FinanceSystem::hasAnyData()
{
    if (monthlySalary > 0 || monthlySpendingLimit > 0 || transactionCount > 0 || budgetCount > 0)
    {
        return true;
    }

    return false;
}



int FinanceSystem::getTransactionCount()
{
    return transactionCount;
}



int FinanceSystem::getBudgetCount()
{
    return budgetCount;
}



int FinanceSystem::getNextTransactionId()
{
    int highestId = 0;

    for (int i = 0; i < transactionCount; i++)
    {
        if (transactions[i].getId() > highestId)
        {
            highestId = transactions[i].getId();
        }
    }

    return highestId + 1;
}



int FinanceSystem::getNextBudgetId()
{
    int highestId = 0;

    for (int i = 0; i < budgetCount; i++)
    {
        if (budgets[i].getBudgetId() > highestId)
        {
            highestId = budgets[i].getBudgetId();
        }
    }

    return highestId + 1;
}



Transaction* FinanceSystem::getTransactionAt(int index)
{
    if (index >= 0 && index < transactionCount)
    {
        return &transactions[index];
    }

    return nullptr;
}



Budget* FinanceSystem::getBudgetAt(int index)
{
    if (index >= 0 && index < budgetCount)
    {
        return &budgets[index];
    }

    return nullptr;
}



double FinanceSystem::getTotalIncome()
{
    double total = monthlySalary;

    for (int i = 0; i < transactionCount; i++)
    {
        if (transactions[i].getTransactionType() == "Income")
        {
            total = total + transactions[i].getAmount();
        }
    }

    return total;
}



double FinanceSystem::getTotalExpense()
{
    double total = 0;

    for (int i = 0; i < transactionCount; i++)
    {
        if (transactions[i].getTransactionType() == "Expense")
        {
            total = total + transactions[i].getAmount();
        }
    }

    return total;
}



double FinanceSystem::getBalance()
{
    return monthlySalary - getTotalExpense();
}



double FinanceSystem::getTotalBudgetLimit()
{
    double total = 0;

    for (int i = 0; i < budgetCount; i++)
    {
        total = total + budgets[i].getLimitAmount();
    }

    return total;
}



double FinanceSystem::getTotalBudgetUsed()
{
    double total = 0;

    for (int i = 0; i < budgetCount; i++)
    {
        total = total + budgets[i].getUsedAmount();
    }

    return total;
}



double FinanceSystem::getRemainingSpendLimit()
{
    return monthlySpendingLimit - getTotalBudgetUsed();
}
