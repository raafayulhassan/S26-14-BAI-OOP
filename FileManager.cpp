#include "filemanager.h"



FileManager::FileManager()
{

}



void FileManager::saveTransactions(Transaction transactions[], int size)
{
    saveTransactionsToFile(transactions, size, "transactions.txt");

    cout << "Transactions saved successfully." << endl;
}



void FileManager::loadTransactions(Transaction transactions[], int& size, int capacity)
{
    loadTransactionsFromFile(transactions, size, capacity, "transactions.txt");

    cout << "Transactions loaded successfully." << endl;
}



void FileManager::saveBudgets(Budget budgets[], int size)
{
    saveBudgetsToFile(budgets, size, "budgets.txt");

    cout << "Budgets saved successfully." << endl;
}



void FileManager::loadBudgets(Budget budgets[], int& size, int capacity)
{
    loadBudgetsFromFile(budgets, size, capacity, "budgets.txt");

    cout << "Budgets loaded successfully." << endl;
}



void FileManager::saveTransactionsToFile(Transaction transactions[], int size, string fileName)
{
    ofstream file;

    file.open(fileName);


    for (int i = 0; i < size; i++)
    {
        file << transactions[i].getTransactionType() << endl;
        file << transactions[i].getId() << endl;
        file << transactions[i].getAmount() << endl;
        file << transactions[i].getDate() << endl;
        file << transactions[i].getDescription() << endl;
        file << transactions[i].getCategoryName() << endl;
    }


    file.close();
}



bool FileManager::loadTransactionsFromFile(Transaction transactions[], int& size, int capacity, string fileName)
{
    ifstream file;

    file.open(fileName);


    size = 0;


    if (file.is_open() == false)
    {
        return false;
    }


    string type;
    string idText;
    string amountText;
    string date;
    string description;
    string categoryName;


    for (int i = 0; i < capacity; i++)
    {
        if (getline(file, type))
        {
            getline(file, idText);
            getline(file, amountText);
            getline(file, date);
            getline(file, description);
            getline(file, categoryName);


            Transaction temp(stoi(idText), stod(amountText), date, description, categoryName, type);

            transactions[size] = temp;

            size++;
        }
    }


    file.close();

    return true;
}



void FileManager::saveBudgetsToFile(Budget budgets[], int size, string fileName)
{
    ofstream file;

    file.open(fileName);


    for (int i = 0; i < size; i++)
    {
        file << budgets[i].getBudgetId() << endl;
        file << budgets[i].getCategoryName() << endl;
        file << budgets[i].getLimitAmount() << endl;
        file << budgets[i].getUsedAmount() << endl;
    }


    file.close();
}



bool FileManager::loadBudgetsFromFile(Budget budgets[], int& size, int capacity, string fileName)
{
    ifstream file;

    file.open(fileName);


    size = 0;


    if (file.is_open() == false)
    {
        return false;
    }


    string budgetIdText;
    string categoryName;
    string limitAmountText;
    string usedAmountText;


    for (int i = 0; i < capacity; i++)
    {
        if (getline(file, budgetIdText))
        {
            getline(file, categoryName);
            getline(file, limitAmountText);
            getline(file, usedAmountText);


            Budget temp(stoi(budgetIdText), categoryName, stod(limitAmountText), stod(usedAmountText));

            budgets[size] = temp;

            size++;
        }
    }


    file.close();

    return true;
}



void FileManager::saveBudgetDomainsToFile(Budget budgets[], int size, string fileName)
{
    ofstream file;

    file.open(fileName);


    for (int i = 0; i < size; i++)
    {
        file << budgets[i].getBudgetId() << endl;
        file << budgets[i].getCategoryName() << endl;
        file << budgets[i].getLimitAmount() << endl;
    }


    file.close();
}



bool FileManager::loadBudgetDomainsFromFile(Budget budgets[], int& size, int capacity, string fileName)
{
    ifstream file;

    file.open(fileName);


    size = 0;


    if (file.is_open() == false)
    {
        return false;
    }


    string budgetIdText;
    string categoryName;
    string limitAmountText;


    for (int i = 0; i < capacity; i++)
    {
        if (getline(file, budgetIdText))
        {
            getline(file, categoryName);
            getline(file, limitAmountText);


            Budget temp(stoi(budgetIdText), categoryName, stod(limitAmountText), 0);

            budgets[size] = temp;

            size++;
        }
    }


    file.close();

    return true;
}


void FileManager::saveMonthInfo(string fileName, string month, double salary, double spendingLimit)
{
    ofstream file;

    file.open(fileName);


    file << month << endl;
    file << salary << endl;
    file << spendingLimit << endl;


    file.close();
}



bool FileManager::loadMonthInfo(string fileName, string& month, double& salary, double& spendingLimit)
{
    ifstream file;

    file.open(fileName);


    if (file.is_open() == false)
    {
        salary = 0;
        spendingLimit = 0;

        return false;
    }


    string salaryText;
    string spendingLimitText;

    getline(file, month);
    getline(file, salaryText);
    getline(file, spendingLimitText);


    salary = stod(salaryText);
    spendingLimit = stod(spendingLimitText);


    file.close();

    return true;
}
